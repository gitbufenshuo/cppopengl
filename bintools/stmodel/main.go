package stmodel

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math"
	"math/rand"
	"os"
	"path"
	"strconv"
	"strings"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

// xyz uv nxnynz
var base_cube = []float32{
	-0.5, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, -1.0, 0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, -1.0, 0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, -1.0, -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 0.0, -1.0, -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, 0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, -0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, -0.5, 0.5, 0.5, 1.0, 0.0, -1.0, 0.0, 0.0, -0.5, 0.5, -0.5, 1.0, 1.0, -1.0, 0.0, 0.0, -0.5, -0.5, -0.5, 0.0, 1.0, -1.0, 0.0, 0.0, -0.5, -0.5, 0.5, 0.0, 0.0, -1.0, 0.0, 0.0, 0.5, 0.5, 0.5, 1.0, 0.0, 1.0, 0.0, 0.0, 0.5, 0.5, -0.5, 1.0, 1.0, 1.0, 0.0, 0.0, 0.5, -0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0, 0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0, -0.5, -0.5, -0.5, 0.0, 1.0, 0.0, -1.0, 0.0, 0.5, -0.5, -0.5, 1.0, 1.0, 0.0, -1.0, 0.0, 0.5, -0.5, 0.5, 1.0, 0.0, 0.0, -1.0, 0.0, -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, -1.0, 0.0, -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1.0, 0.0, -0.5, 0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 0.0}
var base_cube_index = []uint16{
	0, 2, 1, 0, 3, 2,
	4, 5, 6, 4, 6, 7,
	8, 9, 11, 9, 10, 11,
	13, 12, 15, 15, 14, 13,
	16, 17, 18, 16, 18, 19,
	20, 23, 22, 22, 21, 20,
}
var base_cube_attrib = []int32{ // unsigned short in c++
	3, 3, 2,
}

/*
	model
	1. gen baseDir bin_buffer cube x,y,z,px,py,pz
	2. show baseDir
	eg:
	./bintools.out model gen baseDir new cube 1,1,1,0,0,0
*/

func _gencube(baseDir, bin_buffer string, x, y, z, px, py, pz float32) {
	copy_cube := make([]float32, len(base_cube))
	copy(copy_cube, base_cube)
	// 先把uv和normal换回来
	var u, v float32
	for index := 0; index < len(copy_cube); index += 8 {
		u, v = copy_cube[index+3], copy_cube[index+4]
		copy_cube[index+3] = copy_cube[index+5]
		copy_cube[index+4] = copy_cube[index+6]
		copy_cube[index+5] = copy_cube[index+7]
		copy_cube[index+6] = u
		copy_cube[index+7] = v
	}
	// 修正 xyz
	for index := 0; index < len(copy_cube); index += 8 {
		copy_cube[index+0] = copy_cube[index+0] * x
		copy_cube[index+1] = copy_cube[index+1] * y
		copy_cube[index+2] = copy_cube[index+2] * z
	}
	// 修正 px py pz 就是中心点偏移
	xoffset := -(x / 2) * px
	yoffset := -(y / 2) * py
	zoffset := -(z / 2) * pz
	for index := 0; index < len(copy_cube); index += 8 {
		copy_cube[index+0] += xoffset
		copy_cube[index+1] += yoffset
		copy_cube[index+2] += zoffset
	}
	// ebo
	copy_ebo := make([]uint16, len(base_cube_index))
	copy(copy_ebo, base_cube_index)
	// attri
	copy_attrib := make([]int32, len(base_cube_attrib))
	copy(copy_attrib, base_cube_attrib)
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
	bin_buffer_name := fmt.Sprintf("cube_%d%d%d%d%d.bin_buffer", rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10)
	full_buffer_name := path.Join(baseDir, "bin_buffer", bin_buffer_name)
	ioutil.WriteFile(full_buffer_name, buffer.Bytes(), 0644)
	// 2. model 文件
	var model comm.PBModel
	model.BinBuffer = bin_buffer_name
	model.Length = int32(buffer.Len())
	model.EboLength = int32(len(base_cube_index) * 2) // 一个两字节
	model.EboType = 5123                              // unsigned short
	model.Attrib = []int32{3, 3, 2}                   //xyz nx ny nz uv
	model_data, _ := proto.Marshal(&model)
	model_name := fmt.Sprintf("%d%d%d%d%d.model.pb", rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10)
	full_model_name := path.Join(baseDir, "model", model_name)
	ioutil.WriteFile(full_model_name, model_data, 0644)
}

func _gen(baseDir, bin_buffer, shape string) {
	if shape == "cube" {
		segs := strings.Split(os.Args[6], ",")
		x, _ := strconv.ParseFloat(segs[0], 32)
		y, _ := strconv.ParseFloat(segs[1], 32)
		z, _ := strconv.ParseFloat(segs[2], 32)
		px, _ := strconv.ParseFloat(segs[3], 32)
		py, _ := strconv.ParseFloat(segs[4], 32)
		pz, _ := strconv.ParseFloat(segs[5], 32)
		_gencube(baseDir, bin_buffer, float32(x), float32(y), float32(z), float32(px), float32(py), float32(pz))
	}
}

func _show(baseDir, model string) {
	full_name := path.Join(baseDir, "model", model)
	data, _ := ioutil.ReadFile(full_name)
	var pbmodel comm.PBModel
	proto.Unmarshal(data, &pbmodel)
	json_data, _ := json.Marshal(&pbmodel)
	fmt.Println(string(json_data))
}

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	name := os.Args[4]
	if kind == "gen" {
		_gen(baseDir, name, os.Args[5])
	} else {
		_show(baseDir, name)
	}
}
