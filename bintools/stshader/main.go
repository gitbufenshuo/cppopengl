package stshader

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"path"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

// ./bintools.out shader gen baseDir vsname fsname
func _gen(baseDir, vs, fs string) {
	var res comm.PBShaderProgram
	//
	res.Vs = path.Join(baseDir, "shader_code", vs)
	res.Fs = path.Join(baseDir, "shader_code", fs)
	//
	data, _ := proto.Marshal(&res)
	filename := fmt.Sprintf("%d%d%d%d%d.sp.pb", rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10)
	fmt.Printf("Gen: %s\n", filename)
	fullpath := path.Join(baseDir, "shader_program", filename)
	ioutil.WriteFile(fullpath, data, 0644)
}

// ./bintools.out shader show baseDir shadername
func _show(baseDir, name string) {
	fullpath := path.Join(baseDir, "shader_program", name)

	var res comm.PBShaderProgram

	data, _ := ioutil.ReadFile(fullpath)
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	//
	if kind == "gen" {
		_gen(baseDir, os.Args[4], os.Args[5])
	} else {
		_show(baseDir, os.Args[4])
	}
}
