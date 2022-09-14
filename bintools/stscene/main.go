package stscene

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

// 需要手动起个名字
// ./bintools.out scene gen baseDir scene_name "json scene"
func _gen(baseDir, scene_name, json_scene string) {
	var res comm.PBScene
	json.Unmarshal([]byte(json_scene), &res)
	protodata, _ := proto.Marshal(&res)
	fullpath := path.Join(baseDir, "scene", scene_name)
	os.Remove(fullpath) // 覆盖
	ioutil.WriteFile(fullpath, protodata, 0644)
}

// ./bintools.out shader show baseDir shadername
func _show(baseDir, scene_name string) {
	fullpath := path.Join(baseDir, "scene", scene_name)
	data, _ := ioutil.ReadFile(fullpath)
	var res comm.PBScene
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
