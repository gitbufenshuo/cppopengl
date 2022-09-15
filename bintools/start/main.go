package start

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
	1. gen baseDir new_name "art_name" "bin_data"
	2. show baseDir image
	eg:
	gen baseDir phong_pearl.al.pb "mc::asset::ArtLogicPhong" "0.25,0.20725,0.20725,1,0.829,0.829,0.296648,0.296648,0.296648,0.088"
	             资源名称
	show baseDir phong_pearl.al.pb
*/

func _gen(baseDir, new_name, art_name, bin_data string) {
	var res comm.PBArtLogic
	res.LogicClass = art_name
	res.Properties = bin_data
	full_path := path.Join(baseDir, "art_logic", new_name)
	os.Remove(full_path)
	protodata, _ := proto.Marshal(&res)
	ioutil.WriteFile(full_path, protodata, 0644)
}

func _show(baseDir, new_name string) {
	fullpath := path.Join(baseDir, "art_logic", new_name)
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
