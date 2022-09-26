package stdirspec

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"path/filepath"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

/*
扫描 baseDir
生成一个 pb 文件
Eigine可以加载此文件
*/

func Main(baseDir string) {
	var res comm.PBDirSpec
	res.BaseDir = baseDir
	onedir(&res, "image", &res.ImageList)
	onedir(&res, "light", &res.LightList)
	onedir(&res, "bin_buffer", &res.BinBufferList)
	onedir(&res, "shader_code", &res.ShaderCodeList)
	onedir(&res, "art_logic", &res.ArtLogicList)
	onedir(&res, "act_logic", &res.ActLogicList)
	onedir(&res, "texture", &res.TextureList)
	onedir(&res, "model", &res.ModelList)
	onedir(&res, "shader_program", &res.ShaderProgramList)
	onedir(&res, "material", &res.MaterialList)
	onedir(&res, "scene", &res.SceneList)
	onedir(&res, "node", &res.NodeList)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
	protodata, _ := proto.Marshal(&res)
	os.Remove("gogogo.pb.data")
	ioutil.WriteFile("gogogo.pb.data", protodata, 0644)
}

func onedir(res *comm.PBDirSpec, dir string, list *[]string) {
	fmt.Printf("Visited: %s\n", dir)
	full_dir := path.Join(res.BaseDir, dir)
	var visit = func(path string, f os.FileInfo, err error) error {
		if f != nil && !f.IsDir() {
			fmt.Printf("	- add:[fname: %s]\n", f.Name())
			*list = append(*list, f.Name())
		}
		return nil
	}
	filepath.Walk(full_dir, visit)
}
