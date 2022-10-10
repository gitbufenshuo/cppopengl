/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
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
	g_model_kind      *string
	g_model_name      *string
	g_model_shape     *string
	g_model_parameter *string
)

var modelCmd = &cobra.Command{
	Use:   "model",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("model called")
		do_model()
	},
}

func init() {
	rootCmd.AddCommand(modelCmd)
	g_model_kind = modelCmd.Flags().String("kind", "show", "gen/show")
	g_model_name = modelCmd.Flags().String("name", "", "")
	g_model_shape = modelCmd.Flags().String("shape", "cube", "cube")
	g_model_parameter = modelCmd.Flags().String("parameter", "1,1,1,0,0,0", "parameter")
}

// xyz uv nxnynz
var base_cube = []float32{
	-0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, -1.0, //
	0.5, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, -1.0, //
	0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 0.0, -1.0, //
	-0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, -1.0, //

	-0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, //
	0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, //
	0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, //
	-0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, //

	-0.5, 0.5, 0.5, 1.0, 1.0, -1.0, 0.0, 0.0, //
	-0.5, 0.5, -0.5, 0.0, 1.0, -1.0, 0.0, 0.0, //
	-0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0, //
	-0.5, -0.5, 0.5, 1.0, 0.0, -1.0, 0.0, 0.0, //

	0.5, 0.5, 0.5, 0.0, 1.0, 1.0, 0.0, 0.0, //
	0.5, 0.5, -0.5, 1.0, 1.0, 1.0, 0.0, 0.0, //
	0.5, -0.5, -0.5, 1.0, 1.0, 1.0, 0.0, 0.0, //
	0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0, //

	-0.5, -0.5, -0.5, 0.0, 0.0, 0.0, -1.0, 0.0, //
	0.5, -0.5, -0.5, 1.0, 0.0, 0.0, -1.0, 0.0, //
	0.5, -0.5, 0.5, 1.0, 1.0, 0.0, -1.0, 0.0, //
	-0.5, -0.5, 0.5, 0.0, 1.0, 0.0, -1.0, 0.0, //

	-0.5, 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 0.0, //
	0.5, 0.5, -0.5, 1.0, 0.0, 0.0, 1.0, 0.0, //
	0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 1.0, 0.0, //
	-0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0, //
}
var base_cube_index = []uint16{
	0, 2, 1, //
	0, 3, 2, //
	4, 5, 6, //
	4, 6, 7, //
	8, 9, 11, //
	9, 10, 11, //
	13, 12, 15, //
	15, 14, 13, //
	16, 17, 18, //
	16, 18, 19, //
	20, 23, 22, //
	22, 21, 20,
}
var base_cube_attrib = []int32{ // unsigned short in c++
	3, 2, 3, 3, 3,
}

/*
	model
	1. gen baseDir bin_buffer cube x,y,z,px,py,pz
	2. show baseDir
	eg:
	./bintools.out model gen baseDir new cube 1,1,1,0,0,0
*/

func _gencube(baseDir, name string, x, y, z, px, py, pz float32) {
	ver_count := len(base_cube_index)
	copy_cube := make([]float32, ver_count*14)
	xoffset := -(x / 2) * px
	yoffset := -(y / 2) * py
	zoffset := -(z / 2) * pz
	for idx := 0; idx < ver_count; idx++ {
		// xyz
		copy_cube[idx*14] = base_cube[base_cube_index[idx]*8]*x + xoffset
		copy_cube[idx*14+1] = base_cube[base_cube_index[idx]*8+1]*y + yoffset
		copy_cube[idx*14+2] = base_cube[base_cube_index[idx]*8+2]*z + zoffset
		// uv
		copy_cube[idx*14+3] = base_cube[base_cube_index[idx]*8+3]
		copy_cube[idx*14+4] = base_cube[base_cube_index[idx]*8+4]
		// normal
		copy_cube[idx*14+5] = base_cube[base_cube_index[idx]*8+5]
		copy_cube[idx*14+6] = base_cube[base_cube_index[idx]*8+6]
		copy_cube[idx*14+7] = base_cube[base_cube_index[idx]*8+7]
		if (idx+1)%3 != 0 {
			continue
		}
		// 补充 T 和 B
		baseIDX := (idx - 2) * 14
		P1_x := copy_cube[baseIDX+14] - copy_cube[baseIDX]
		P1_y := copy_cube[baseIDX+15] - copy_cube[baseIDX+1]
		P1_z := copy_cube[baseIDX+16] - copy_cube[baseIDX+2]

		P2_x := copy_cube[baseIDX+28] - copy_cube[baseIDX]
		P2_y := copy_cube[baseIDX+29] - copy_cube[baseIDX+1]
		P2_z := copy_cube[baseIDX+30] - copy_cube[baseIDX+2]

		S1, T1 := copy_cube[baseIDX+17]-copy_cube[baseIDX+3], copy_cube[baseIDX+18]-copy_cube[baseIDX+4]
		S2, T2 := copy_cube[baseIDX+31]-copy_cube[baseIDX+3], copy_cube[baseIDX+32]-copy_cube[baseIDX+4]

		factor := 1 / (S1*T2 - S2*T1)
		Tx, Bx := factor*(T2*P1_x-T1*P2_x), factor*(-S2*P1_x+S1*P2_x)
		Ty, By := factor*(T2*P1_y-T1*P2_y), factor*(-S2*P1_y+S1*P2_y)
		Tz, Bz := factor*(T2*P1_z-T1*P2_z), factor*(-S2*P1_z+S1*P2_z)

		copy_cube[baseIDX+11], copy_cube[baseIDX+12], copy_cube[baseIDX+13] = Tx, Ty, Tz
		copy_cube[baseIDX+11+14], copy_cube[baseIDX+12+14], copy_cube[baseIDX+13+14] = Tx, Ty, Tz
		copy_cube[baseIDX+11+28], copy_cube[baseIDX+12+28], copy_cube[baseIDX+13+28] = Tx, Ty, Tz

		copy_cube[baseIDX+8], copy_cube[baseIDX+9], copy_cube[baseIDX+10] = Bx, By, Bz
		copy_cube[baseIDX+8+14], copy_cube[baseIDX+9+14], copy_cube[baseIDX+10+14] = Bx, By, Bz
		copy_cube[baseIDX+8+28], copy_cube[baseIDX+9+28], copy_cube[baseIDX+10+28] = Bx, By, Bz
	}
	// ebo
	copy_ebo := make([]uint16, len(base_cube_index))
	for idx := range copy_ebo {
		copy_ebo[idx] = uint16(idx)
	}
	// attri
	copy_attrib := make([]int32, len(base_cube_attrib))
	copy(copy_attrib, base_cube_attrib)
	if *g_verbose {
		// 打印一下
		for idx := 0; idx < len(copy_cube); idx += 14 {
			fmt.Printf("P:(%f,%f,%f) UV:(%f,%f) N:(%f,%f,%f) B:(%f,%f,%f) T:(%f,%f,%f)\n",
				copy_cube[idx], copy_cube[idx+1], copy_cube[idx+2],
				copy_cube[idx+3], copy_cube[idx+4],
				copy_cube[idx+5], copy_cube[idx+6], copy_cube[idx+7],
				copy_cube[idx+8], copy_cube[idx+9], copy_cube[idx+10],
				copy_cube[idx+11], copy_cube[idx+12], copy_cube[idx+13],
			)
		}
	}
	// 写入 pb 文件(model 文件 和 bin_buffer 文件)
	// 1. bin_buffer
	// 1.1 ebo
	buffer := new(bytes.Buffer)
	for idx := range copy_ebo {
		buffer.WriteByte(byte(copy_ebo[idx] % 256))
		buffer.WriteByte(byte(copy_ebo[idx] / 256))
	}
	// 1.2 vbo
	bytelist := make([]byte, 4)
	for idx := range copy_cube {
		u32 := math.Float32bits(copy_cube[idx])
		binary.LittleEndian.PutUint32(bytelist, u32)
		buffer.Write(bytelist)
	}
	bin_buffer_name := fmt.Sprintf("cube_%s.bin_buffer", name)
	full_buffer_name := path.Join(baseDir, "bin_buffer", bin_buffer_name)
	os.Remove(full_buffer_name)
	ioutil.WriteFile(full_buffer_name, buffer.Bytes(), 0644)
	// 2. model 文件
	var model comm.PBModel
	model.BinBuffer = bin_buffer_name
	model.Length = int32(buffer.Len())
	model.EboLength = int32(len(base_cube_index) * 2) // 一个两字节
	model.EboType = 5123                              // unsigned short
	model.Attrib = copy_attrib                        // xyz nx ny nz uv
	model_data, _ := proto.Marshal(&model)
	model_name := fmt.Sprintf("%s.model.pb", name)
	full_model_name := path.Join(baseDir, "model", model_name)
	os.Remove(full_model_name)
	ioutil.WriteFile(full_model_name, model_data, 0644)
}

func _gen(baseDir, name, shape, parameter string) {
	if shape == "cube" {
		segs := strings.Split(parameter, ",")
		x, _ := strconv.ParseFloat(segs[0], 32)
		y, _ := strconv.ParseFloat(segs[1], 32)
		z, _ := strconv.ParseFloat(segs[2], 32)
		px, _ := strconv.ParseFloat(segs[3], 32)
		py, _ := strconv.ParseFloat(segs[4], 32)
		pz, _ := strconv.ParseFloat(segs[5], 32)
		_gencube(baseDir, name, float32(x), float32(y), float32(z), float32(px), float32(py), float32(pz))
	}
}

func _show(baseDir, name string) {
	model_name := fmt.Sprintf("%s.model.pb", name)
	full_name := path.Join(baseDir, "model", model_name)
	data, _ := ioutil.ReadFile(full_name)
	var pbmodel comm.PBModel
	proto.Unmarshal(data, &pbmodel)
	json_data, _ := json.Marshal(&pbmodel)
	fmt.Println(string(json_data))
}

func do_model() {
	kind := *g_model_kind
	baseDir := *g_basedir
	name := *g_model_name
	shape := *g_model_shape
	parameter := *g_model_parameter
	fmt.Println(baseDir, kind, name, shape, parameter)
	if kind == "gen" {
		_gen(baseDir, name, shape, parameter)
	} else {
		_show(baseDir, name)
	}
}
