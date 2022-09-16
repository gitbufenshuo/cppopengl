package stact

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

/*
	art
	1. gen baseDir new_name "act_name" "bin_data"
	2. show baseDir new_name
	eg:
	gen baseDir camera.acl.pb "mc::asset::ActLogicCamera" ""
	             资源名称
	show baseDir camera.acl.pb
*/

func _gen(baseDir, new_name, act_name, bin_data string) {
	var res comm.PBArtLogic
	res.LogicClass = act_name
	res.Properties = bin_data
	full_path := path.Join(baseDir, "act_logic", new_name)
	os.Remove(full_path)
	protodata, _ := proto.Marshal(&res)
	ioutil.WriteFile(full_path, protodata, 0644)
}

func _show(baseDir, new_name string) {
	fullpath := path.Join(baseDir, "act_logic", new_name)
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

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	new_name := os.Args[4]
	if kind == "gen" {
		_gen(
			baseDir,
			new_name,
			os.Args[5],
			os.Args[6],
		)
	} else {
		_show(baseDir, new_name)
	}
}
