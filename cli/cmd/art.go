/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

var (
	g_art_kind    *string
	g_art_name    *string
	g_art_artname *string
	g_art_bindata *string
)

// artCmd represents the art command
var artCmd = &cobra.Command{
	Use:   "art",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("art called")
		do_art()
	},
}

func init() {
	rootCmd.AddCommand(artCmd)

	g_art_kind = artCmd.Flags().String("kind", "show", "gen/show")
	g_art_name = artCmd.Flags().String("name", "", "")
	g_art_artname = artCmd.Flags().String("artname", "", "")
	g_art_bindata = artCmd.Flags().String("bindata", "", "")
}

func art_gen(baseDir, new_name, art_name, bin_data string) {
	var res comm.PBArtLogic
	res.LogicClass = art_name
	res.Properties = bin_data
	filename := fmt.Sprintf("%s.al.pb", new_name)
	full_path := path.Join(baseDir, "art_logic", filename)
	os.Remove(full_path)
	protodata, _ := proto.Marshal(&res)
	ioutil.WriteFile(full_path, protodata, 0644)
}

func art_show(baseDir, new_name string) {
	filename := fmt.Sprintf("%s.al.pb", new_name)
	fullpath := path.Join(baseDir, "art_logic", filename)
	data, err := ioutil.ReadFile(fullpath)
	if err != nil {
		fmt.Println(err)
		return
	}
	var res comm.PBArtLogic
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func do_art() {
	kind := *g_art_kind
	baseDir := *g_basedir
	new_name := *g_art_name
	art_name := *g_art_artname
	bin_data := *g_art_bindata
	if kind == "gen" {
		art_gen(
			baseDir,
			new_name,
			art_name,
			bin_data,
		)
	} else {
		art_show(baseDir, new_name)
	}
}
