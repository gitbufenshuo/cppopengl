package stmaterial

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"path"
	"strings"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

// ./bintools.out material gen baseDir logic_class t1,t2,t3 shader_program
func _gen(baseDir, art_logic, tlist, shader_program string) {
	var res comm.PBMaterial
	res.ArtLogic = art_logic
	{
		segs := strings.Split(tlist, ",")
		for _, onet := range segs {
			res.TextureList = append(res.TextureList,
				path.Join(baseDir, "texture", onet),
			)
		}
	}
	res.ShaderProgram = path.Join(baseDir, "shader_program", shader_program)
	protodata, _ := proto.Marshal(&res)
	filename := fmt.Sprintf("%d%d%d%d%d.material.pb", rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10, rand.Int()%10)
	fmt.Println("Gen: ", filename)
	fullpath := path.Join(baseDir, "material", filename)
	ioutil.WriteFile(fullpath, protodata, 0644)
}

// ./bintools.out shader show baseDir shadername
func _show(baseDir, name string) {
	fullpath := path.Join(baseDir, "material", name)
	data, _ := ioutil.ReadFile(fullpath)
	var res comm.PBMaterial
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	//
	if kind == "gen" {
		_gen(baseDir, os.Args[4], os.Args[5], os.Args[6])
	} else {
		_show(baseDir, os.Args[4])
	}
}
