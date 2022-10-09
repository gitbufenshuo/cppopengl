/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"bufio"
	"bytes"
	"encoding/binary"
	"fmt"
	"io/ioutil"
	"math"
	"os"
	"path"
	"strconv"
	"strings"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

var (
	g_objfile *string
)

// objConvertCmd represents the objConvert command
var objConvertCmd = &cobra.Command{
	Use:   "objConvert",
	Short: "转换obj格式",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("objConvert 正在执行")
	},
}

func init() {
	rootCmd.AddCommand(objConvertCmd)
	g_objfile = objConvertCmd.Flags().String("obj", "", "")
}

type FElem struct {
	Data []int
}

func stofloat32(input string) float32 {
	v, _ := strconv.ParseFloat(input, 32)
	return float32(v)
}
func stoint(input string) int {
	v, _ := strconv.Atoi(input)
	return v
}
func stoFELM(input string) FElem {
	segs := strings.Split(input, "/")
	var res FElem
	for _, one := range segs {
		res.Data = append(res.Data, stoint(one))
	}
	return res
}

// return 1. bin_buffer
// return 2. model pb
func loadObj(filename string) ([]byte, *comm.PBModel) {
	v_list := make([]float32, 0, 0)
	vt_list := make([]float32, 0, 0)
	vn_list := make([]float32, 0, 0)
	f_list := make([]FElem, 0, 0)
	fline := 0
	//
	file, _ := os.OpenFile(filename, os.O_RDONLY, 0644)
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		text := scanner.Text()
		if strings.HasPrefix(text, "v ") {
			text = strings.TrimPrefix(text, "v ")
			segs := strings.Split(text, " ")
			v_list = append(v_list, stofloat32(segs[0]))
			v_list = append(v_list, stofloat32(segs[1]))
			v_list = append(v_list, stofloat32(segs[2]))
		} else if strings.HasPrefix(text, "vt ") {
			text = strings.TrimPrefix(text, "vt ")
			segs := strings.Split(text, " ")
			vt_list = append(vt_list, stofloat32(segs[0]))
			vt_list = append(vt_list, stofloat32(segs[1]))
		} else if strings.HasPrefix(text, "vn ") {
			text = strings.TrimPrefix(text, "vn ")
			segs := strings.Split(text, " ")
			vn_list = append(vn_list, stofloat32(segs[0]))
			vn_list = append(vn_list, stofloat32(segs[1]))
			vn_list = append(vn_list, stofloat32(segs[2]))
		} else if strings.HasPrefix(text, "f ") {
			text = strings.TrimPrefix(text, "f ")
			segs := strings.Split(text, " ")
			for _, one := range segs {
				f_list = append(f_list, stoFELM(one))
			}
			fline = len(segs)
		}
	}
	fmt.Println(v_list)
	fmt.Println(vt_list)
	fmt.Println(vn_list)
	fmt.Println(f_list)
	//
	ebo_list := make([]int, 0, 0)
	vbo_list := make([]float32, 0, 0)
	//
	for _, onef := range f_list {
		// 坐标3 uv2 N3 B3 T3
		{
			// 坐标3
			vbo_list = append(vbo_list, v_list[(onef.Data[0]-1)*3]/30)
			vbo_list = append(vbo_list, v_list[(onef.Data[0]-1)*3+1]/30)
			vbo_list = append(vbo_list, v_list[(onef.Data[0]-1)*3+2]/30)
		}
		{
			// uv2
			vbo_list = append(vbo_list, vt_list[(onef.Data[1]-1)*2])
			vbo_list = append(vbo_list, vt_list[(onef.Data[1]-1)*2+1])
		}
		{
			// N3
			vbo_list = append(vbo_list, vn_list[(onef.Data[2]-1)*3])
			vbo_list = append(vbo_list, vn_list[(onef.Data[2]-1)*3+1])
			vbo_list = append(vbo_list, vn_list[(onef.Data[2]-1)*3+2])
		}
		{
			// B3
			vbo_list = append(vbo_list, 1)
			vbo_list = append(vbo_list, 1)
			vbo_list = append(vbo_list, 1)
		}
		{
			// T3
			vbo_list = append(vbo_list, 1)
			vbo_list = append(vbo_list, 1)
			vbo_list = append(vbo_list, 1)
		}
	}
	if fline == 4 {
		for index := 0; index < len(f_list); index += fline {
			ebo_list = append(ebo_list, index, index+1, index+2)
			ebo_list = append(ebo_list, index, index+2, index+3)
		}
	} else if fline == 3 {
		for index := 0; index < len(f_list); index += fline {
			ebo_list = append(ebo_list, index, index+1, index+2)
		}
		// 计算 Tangent 和 BiTangent
		for idx := 0; idx < len(vbo_list); idx += 42 { // 三个点一算
			P1_x := vbo_list[idx+14] - vbo_list[idx]
			P1_y := vbo_list[idx+15] - vbo_list[idx+1]
			P1_z := vbo_list[idx+16] - vbo_list[idx+2]

			P2_x := vbo_list[idx+28] - vbo_list[idx]
			P2_y := vbo_list[idx+29] - vbo_list[idx+1]
			P2_z := vbo_list[idx+30] - vbo_list[idx+2]

			S1, T1 := vbo_list[idx+17]-vbo_list[idx+3], vbo_list[idx+18]-vbo_list[idx+4]
			S2, T2 := vbo_list[idx+31]-vbo_list[idx+3], vbo_list[idx+32]-vbo_list[idx+4]

			factor := 1 / (S1*T2 - S2*T1)
			Tx, Bx := factor*(T2*P1_x-T1*P2_x), factor*(-S2*P1_x+S1*P2_x)
			Ty, By := factor*(T2*P1_y-T1*P2_y), factor*(-S2*P1_y+S1*P2_y)
			Tz, Bz := factor*(T2*P1_z-T1*P2_z), factor*(-S2*P1_z+S1*P2_z)

			vbo_list[idx+11], vbo_list[idx+12], vbo_list[idx+13] = Tx, Ty, Tz
			vbo_list[idx+11+14], vbo_list[idx+12+14], vbo_list[idx+13+14] = Tx, Ty, Tz
			vbo_list[idx+11+28], vbo_list[idx+12+28], vbo_list[idx+13+28] = Tx, Ty, Tz

			vbo_list[idx+8], vbo_list[idx+9], vbo_list[idx+10] = Bx, By, Bz
			vbo_list[idx+8+14], vbo_list[idx+9+14], vbo_list[idx+10+14] = Bx, By, Bz
			vbo_list[idx+8+28], vbo_list[idx+9+28], vbo_list[idx+10+28] = Bx, By, Bz

		}
	}
	// 写入 bin_buffer 目录
	buffer := new(bytes.Buffer)
	// ebo
	var ebo_length int32
	var ebo_type int32
	for _, oneindex := range ebo_list {
		if len(ebo_list) <= 65535 {
			// unsigned short 即可
			buffer.WriteByte(byte(oneindex % 256))
			buffer.WriteByte(byte(oneindex / 256))
			ebo_length += 2
			ebo_type = 5123
		} else {
			// unsigned int 即可
			buffer.WriteByte(byte(oneindex % 256))
			oneindex /= 256
			buffer.WriteByte(byte(oneindex % 256))
			oneindex /= 256
			buffer.WriteByte(byte(oneindex % 256))
			oneindex /= 256
			buffer.WriteByte(byte(oneindex % 256))
			ebo_length += 4
			ebo_type = 5125
		}
	}
	// vbo
	bytelist := make([]byte, 4)
	for idx := range vbo_list {
		u32 := math.Float32bits(vbo_list[idx])
		binary.LittleEndian.PutUint32(bytelist, u32)
		buffer.Write(bytelist)
	}
	// model
	var model comm.PBModel
	{
		// model.BinBuffer = bin_buffer_name
		model.Length = int32(buffer.Len())
		model.EboLength = ebo_length
		model.EboType = ebo_type              // unsigned short
		model.Attrib = []int32{3, 2, 3, 3, 3} //xyz uv N B T
	}
	return buffer.Bytes(), &model
}

// 将一个obj格式转成 glbinbuffer 格式
// 然后生成 model 和 bin_buffer
// ./bintools.out obj baseDir xxx.obj
func Main() {
	baseDir := *g_basedir
	objFile := *g_objfile
	//
	objf, err := os.Lstat(objFile)
	if err != nil {
		fmt.Println(objFile, "不存在", err)
		return
	}
	fmt.Println("找到文件：", objf.Name(), " 即将处理此文件，转格式成 bin_buffer")
	if !strings.HasSuffix(objf.Name(), ".obj") {
		fmt.Println("后缀名必须是 .obj, 程序退出")
		return
	}
	//
	binbufferdata, modelpb := loadObj(objFile)
	//
	modelName := fmt.Sprintf("%s.model.pb", objf.Name())
	binBufferName := fmt.Sprintf("%s.bin_buffer", objf.Name())
	modelPath := path.Join(baseDir, "model", modelName)
	binBufferPath := path.Join(baseDir, "bin_buffer", binBufferName)
	// 先删除已有的
	os.Remove(modelPath)
	os.Remove(binBufferPath)
	//
	modelpb.BinBuffer = binBufferName
	ioutil.WriteFile(binBufferPath, binbufferdata, 0644)
	{
		modeldata, _ := proto.Marshal(modelpb)
		ioutil.WriteFile(modelPath, modeldata, 0644)
	}
	fmt.Println("GenBinBuffer:", binBufferPath)
	fmt.Println("GenModel:", modelPath)
}
