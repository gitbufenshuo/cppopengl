package stmodel

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strconv"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

// xyz uv nxnynz
var base_cube = []float32{
	-0.5, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, -1.0, 0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, -1.0, 0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, -1.0, -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 0.0, -1.0, -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.5, -0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0, 0.5, 0.5, 0.5, 1.0, 1.0, 0.0, 0.0, 1.0, -0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, -0.5, 0.5, 0.5, 1.0, 0.0, -1.0, 0.0, 0.0, -0.5, 0.5, -0.5, 1.0, 1.0, -1.0, 0.0, 0.0, -0.5, -0.5, -0.5, 0.0, 1.0, -1.0, 0.0, 0.0, -0.5, -0.5, 0.5, 0.0, 0.0, -1.0, 0.0, 0.0, 0.5, 0.5, 0.5, 1.0, 0.0, 1.0, 0.0, 0.0, 0.5, 0.5, -0.5, 1.0, 1.0, 1.0, 0.0, 0.0, 0.5, -0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0, 0.5, -0.5, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0, -0.5, -0.5, -0.5, 0.0, 1.0, 0.0, -1.0, 0.0, 0.5, -0.5, -0.5, 1.0, 1.0, 0.0, -1.0, 0.0, 0.5, -0.5, 0.5, 1.0, 0.0, 0.0, -1.0, 0.0, -0.5, -0.5, 0.5, 0.0, 0.0, 0.0, -1.0, 0.0, -0.5, 0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, -0.5, 1.0, 1.0, 0.0, 1.0, 0.0, 0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 1.0, 0.0, -0.5, 0.5, 0.5, 0.0, 0.0, 0.0, 1.0, 0.0}

/*
	model
	1. gen baseDir bin_buffer cube x,y,z,px,py,pz
	2. show baseDir
	eg:
	gen baseDir new cube 1,1,1,0,0,0
*/

func _gencube(baseDir, bin_buffer string, x, y, z, px, py, pz float32) {
	copy_cube := make([]float32, len(base_cube))
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
		copy_cube[index+1] = copy_cube[index+0] * y
		copy_cube[index+2] = copy_cube[index+0] * z
	}

}

func _gen(baseDir, bin_buffer, kind string) {

}

func _show(baseDir, texture string) {
	fullpath := path.Join(baseDir, "texture", texture)
	data, err := ioutil.ReadFile(fullpath)
	if err != nil {
		fmt.Println(err)
		return
	}
	var res comm.PBTexture
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	image := os.Args[4]
	if kind == "gen" {
		mag, _ := strconv.Atoi(os.Args[5])
		min, _ := strconv.Atoi(os.Args[6])
		s, _ := strconv.Atoi(os.Args[7])
		t, _ := strconv.Atoi(os.Args[8])
		_gen(
			baseDir,
			image,
			mag,
			min,
			s,
			t,
		)
	} else {
		_show(baseDir, image)
	}
}
