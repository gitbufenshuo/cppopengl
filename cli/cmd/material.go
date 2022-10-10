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
	"strings"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

var (
	g_material_kind     *string
	g_material_artlogic *string
	g_material_tlist    *string // texture list
	g_material_sp       *string // shader program
	g_material_name     *string //
)

// materialCmd represents the material command
var materialCmd = &cobra.Command{
	Use:   "material",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("material called")
		do_material()
	},
}

func init() {
	rootCmd.AddCommand(materialCmd)
	g_material_kind = materialCmd.Flags().String("kind", "show", "gen/show")
	g_material_artlogic = materialCmd.Flags().String("artlogic", "", "")
	g_material_tlist = materialCmd.Flags().String("tlist", "", "texture list")
	g_material_sp = materialCmd.Flags().String("sp", "", "shader program")
	g_material_name = materialCmd.Flags().String("name", "", "")
}

// ./bintools.out material gen baseDir logic_class t1,t2,t3 shader_program
func material_gen(baseDir, art_logic, tlist, shader_program, name string) {
	var res comm.PBMaterial
	res.ArtLogic = art_logic
	if len(tlist) > 0 {
		segs := strings.Split(tlist, ",")
		for _, onet := range segs {
			res.TextureList = append(res.TextureList, onet)
		}
	}
	res.ShaderProgram = shader_program
	protodata, _ := proto.Marshal(&res)
	filename := fmt.Sprintf("%s.material.pb", name)
	fmt.Println("Gen: ", filename)
	fullpath := path.Join(baseDir, "material", filename)
	os.Remove(fullpath)
	ioutil.WriteFile(fullpath, protodata, 0644)
}

// ./bintools.out shader show baseDir shadername
func material_show(baseDir, name string) {
	filename := fmt.Sprintf("%s.material.pb", name)
	fullpath := path.Join(baseDir, "material", filename)
	data, _ := ioutil.ReadFile(fullpath)
	var res comm.PBMaterial
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func do_material() {
	kind := *g_material_kind
	name := *g_material_name
	sp := *g_material_sp
	artlogic := *g_material_artlogic
	tlist := *g_material_tlist
	baseDir := *g_basedir
	//
	if kind == "gen" {
		material_gen(baseDir, artlogic, tlist, sp, name)
	} else {
		material_show(baseDir, name)
	}
}
