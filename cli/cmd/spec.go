/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"path/filepath"
	"strings"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

// specCmd represents the spec command
var specCmd = &cobra.Command{
	Use:   "spec",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("spec called")
		do_spec()
	},
}

func init() {
	rootCmd.AddCommand(specCmd)
}

var ignore_file = []string{
	".DS_Store",
}

func do_spec() {
	var res comm.PBDirSpec
	res.BaseDir = *g_basedir
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
	path.Join(res.BaseDir, "gogogo.pb.data")
	os.Remove(path.Join(res.BaseDir, "gogogo.pb.data"))
	ioutil.WriteFile(path.Join(res.BaseDir, "gogogo.pb.data"), protodata, 0644)
}

func onedir(res *comm.PBDirSpec, dir string, list *[]string) {
	fmt.Printf("Visited: %s\n", dir)
	full_dir := path.Join(res.BaseDir, dir)
	var visit = func(path string, f os.FileInfo, err error) error {
		for _, oneignore := range ignore_file {
			if strings.Contains(f.Name(), oneignore) {
				return nil
			}
		}
		if f != nil && !f.IsDir() {
			fmt.Printf("	- add:[fname: %s]\n", f.Name())
			*list = append(*list, f.Name())
		}
		return nil
	}
	filepath.Walk(full_dir, visit)
}
