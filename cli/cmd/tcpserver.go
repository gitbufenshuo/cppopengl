/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"net"
	"sync"

	"github.com/spf13/cobra"
)

var (
	g_tcpserver_addr *string
	g_tcpserver_kind *string
)

const (
	MSG_ID_LOGIN uint64 = iota
	MSG_ID_CHAT  uint64 = iota
)
const (
	RP_ID_LOGIN uint64 = iota
	RP_ID_CHAT  uint64 = iota
)

type Client struct {
	conn   net.Conn
	send_q chan []byte
}

func (client *Client) Run() {
	go client.flush()
	go client.read()
}

func (client *Client) read() {
	id_buf := make([]byte, 8)
	len_buf := make([]byte, 8)
	data_buf := make([]byte, 65535)
	var err error
	var id, size uint64
	var first bool = true
	var user_name string
	for {
		err = fix_read(client.conn, id_buf)
		if err != nil {
			client.conn.Close()
			break
		}
		err = fix_read(client.conn, len_buf)
		if err != nil {
			client.conn.Close()
			break
		}
		id, size = parse_id(id_buf), parse_id(len_buf)
		err = fix_read(client.conn, data_buf[:size])
		if err != nil {
			client.conn.Close()
			break
		}
		//
		if first {
			first = false
			if id != 0 {
				client.conn.Close()
				break
			}
			g_lock.Lock()
			user_name = string(data_buf[:size])
			g_client_list[user_name] = client
			// 创建一个 login rp， 发送到所有 client
			buffer := new(bytes.Buffer)
			buffer.Write(id_buf)
			buffer.Write(len_buf)
			buffer.Write(data_buf[:size])
			for _, oneclient := range g_client_list {
				// 里面会拷贝
				oneclient.Send(buffer.Bytes())
			}
			buffer.Reset()
			g_lock.Unlock()
			continue
		}
		//
		buffer := new(bytes.Buffer)
		buffer.Write(id_buf)
		buffer.Write(len_buf)
		buffer.Write(data_buf[:size])
		g_lock.Lock()
		for _, oneclient := range g_client_list {
			// 里面会拷贝
			oneclient.Send(buffer.Bytes())
		}
		buffer.Reset()
		g_lock.Unlock()
	}
}

func (client *Client) flush() {
	// 将 send_q 里面的消息，尽快发出去
	for {
		onemsg := <-client.send_q
		err := fix_write(client.conn, onemsg)
		if err != nil {
			break
		}
	}
	client.conn.Close()
}

func (client *Client) Send(msg []byte) {
	data := make([]byte, len(msg))
	copy(data, msg)
	client.send_q <- data
}

var (
	g_client_list map[string]*Client
	g_lock        sync.Mutex
)

// tcpserverCmd represents the tcpserver command
var tcpserverCmd = &cobra.Command{
	Use:   "tcpserver",
	Short: "简单的tcpserver",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("tcpserver start")
		do_tcpserver()
	},
}

func init() {
	rootCmd.AddCommand(tcpserverCmd)
	g_tcpserver_addr = tcpserverCmd.Flags().String("addr", "0.0.0.0:8888", "default 0.0.0.0:8888")
	g_tcpserver_kind = tcpserverCmd.Flags().String("kind", "chat", "default chat")
}

func fix_read(client net.Conn, buf []byte) error {
	total := 0
	for {
		if total == len(buf) {
			break
		}
		n, err := client.Read(buf[total:])
		if err != nil {
			return err
		}
		total += n
	}
	return nil
}
func fix_write(client net.Conn, buf []byte) error {
	total := 0
	for {
		if total == len(buf) {
			break
		}
		n, err := client.Write(buf[total:])
		if err != nil {
			return err
		}
		total += n
	}
	return nil
}

func parse_id(msg []byte) uint64 {
	return binary.LittleEndian.Uint64(msg)
}
func put_id(id uint64, msg []byte) {
	binary.LittleEndian.PutUint64(msg, id)
}

func do_chat_server() {
	g_client_list = make(map[string]*Client)
	list, err := net.Listen("tcp4", *g_tcpserver_addr)
	if err != nil {
		panic(err)
	}
	fmt.Println("tcp server ok:", list.Addr().String())
	//
	for {
		client, err := list.Accept()
		if err != nil {
			panic(err)
		}
		newClient := new(Client)
		newClient.conn = client
		newClient.send_q = make(chan []byte, 100)
		go newClient.Run()
	}
}

func do_chat_client() {
	server, err := net.Dial("tcp4", *g_tcpserver_addr)
	//
	if err != nil {
		panic(err)
	}
	//
	id_buf := make([]byte, 8)
	len_buf := make([]byte, 8)
	name_buf := []byte("cpp-opengl-client")
	data_buf := []byte("Hello world")
	{
		// login
		id, size := uint64(0), uint64(len(name_buf))
		put_id(id, id_buf)
		put_id(size, len_buf)
		fix_write(server, id_buf)
		fix_write(server, len_buf)
		fix_write(server, name_buf)
	}
	{
		// chat
		id, size := uint64(1), uint64(len(data_buf))
		put_id(id, id_buf)
		put_id(size, len_buf)
		fix_write(server, id_buf)
		fix_write(server, len_buf)
		fix_write(server, data_buf)
	}
	for {
		// read twice
		buffer := make([]byte, 1000)
		fix_read(server, id_buf)
		fix_read(server, len_buf)
		id := parse_id(id_buf)
		size := parse_id(len_buf)
		fix_read(server, buffer[:size])
		fmt.Printf("From server : id(%d), len(%d), data(%s)\n", id, size, string(buffer[:size]))
		//
		fix_read(server, id_buf)
		fix_read(server, len_buf)
		id = parse_id(id_buf)
		size = parse_id(len_buf)
		fix_read(server, buffer[:size])
		fmt.Printf("From server : id(%d), len(%d), data(%s)\n", id, size, string(buffer[:size]))
	}
}

func do_tcpserver() {
	if *g_tcpserver_kind == "chat_server" {
		do_chat_server()
	}
	if *g_tcpserver_kind == "chat_client" {
		do_chat_client()
	}
}
