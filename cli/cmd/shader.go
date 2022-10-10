/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"path"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

var (
	g_shader_vcode *string
	g_shader_fcode *string
	g_shader_name  *string
	g_shader_kind  *string
)

// shaderCmd represents the shader command
var shaderCmd = &cobra.Command{
	Use:   "shader",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("shader called")
		do_shader()
	},
}

func init() {
	rootCmd.AddCommand(shaderCmd)
	g_shader_vcode = shaderCmd.Flags().String("vcode", "", "vertex code")
	g_shader_fcode = shaderCmd.Flags().String("fcode", "", "frag code")
	g_shader_kind = shaderCmd.Flags().String("kind", "", "gen/show")
	g_shader_name = shaderCmd.Flags().String("name", "", "shader name")
}

// ./bintools.out shader gen baseDir vsname fsname
func shader_gen(baseDir, vs, fs, name string) {
	var res comm.PBShaderProgram
	//
	res.Vs = vs
	res.Fs = fs
	//
	data, _ := proto.Marshal(&res)
	filename := fmt.Sprintf("%s.sp.pb", name)
	fmt.Printf("Gen: %s\n", filename)
	fullpath := path.Join(baseDir, "shader_program", filename)
	ioutil.WriteFile(fullpath, data, 0644)
}

// ./bintools.out shader show baseDir shadername
func shader_show(baseDir, name string) {
	filename := fmt.Sprintf("%s.sp.pb", name)
	fullpath := path.Join(baseDir, "shader_program", filename)

	var res comm.PBShaderProgram

	data, _ := ioutil.ReadFile(fullpath)
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func do_shader() {
	kind := *g_shader_kind
	baseDir := *g_basedir
	vcode := *g_shader_vcode
	fcode := *g_shader_fcode
	name := *g_shader_name
	//
	if kind == "gen" {
		shader_gen(baseDir, vcode, fcode, name)
	} else {
		shader_show(baseDir, name)
	}
}
