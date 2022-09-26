package light

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strconv"
	"strings"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

/*
	生成一个新的 example
*/
// ./bintools light gen BaseDir Name "parameters"
// ./bintools light show BaseDir Name

func gen(basedir, name, pars string) {
	var res comm.PBLight
	segs := strings.Split(pars, ",")
	{
		segs_0, _ := strconv.Atoi(segs[0])
		res.Kind = int32(segs_0)
	}
	protodata, _ := proto.Marshal(&res)
	filepath := path.Join(basedir, "light", name)
	os.Remove(filepath)
	ioutil.WriteFile(filepath, protodata, 0644)
}

func show(basedir, name string) {
	var res comm.PBLight
	filepath := path.Join(basedir, "light", name)
	protodata, _ := ioutil.ReadFile(filepath)
	proto.Unmarshal(protodata, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func Main() {
	Kind := os.Args[2]
	BaseDir := os.Args[3]
	Name := os.Args[4]
	if Kind == "gen" {
		Parameters := os.Args[5]
		gen(BaseDir, Name, Parameters)
	} else {
		show(BaseDir, Name)
	}
}
