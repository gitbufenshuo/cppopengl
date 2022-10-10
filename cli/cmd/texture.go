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
	"strconv"
	"strings"

	"gitee.com/onebook/cppopengl/cli/mc/comm"
	"github.com/spf13/cobra"
	"google.golang.org/protobuf/proto"
)

var (
	g_texture_kind      *string
	g_texture_image     *string
	g_texture_name      *string
	g_texture_parameter *string
	g_texture_shape     *string
)

// textureCmd represents the texture command
var textureCmd = &cobra.Command{
	Use:   "texture",
	Short: "",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("texture called")
		do_texture()
	},
}

func init() {
	rootCmd.AddCommand(textureCmd)
	g_texture_kind = textureCmd.Flags().String("kind", "show", "gen/show")
	g_texture_image = textureCmd.Flags().String("image", "", "image file name")
	g_texture_name = textureCmd.Flags().String("name", "", "")
	g_texture_parameter = textureCmd.Flags().String("parameter", "0x2601,0x2601,0x2901,0x2901", "")
	g_texture_shape = textureCmd.Flags().String("shape", "texture", "texture/cubemap")
}

func texture_gen_texture2d(baseDir, image, name string, mag, min, s, t int64) {
	{
		full_image_path := path.Join(baseDir, "image", image)
		finfo, err := os.Lstat(full_image_path)
		if err != nil {
			return
		}
		if finfo == nil {
			return
		}
	}
	var res comm.PBTexture
	res.Image = image
	res.MagFilter = int32(mag)
	res.MinFilter = int32(min)
	res.WrapS = int32(s)
	res.WrapT = int32(t)
	res.TextureType = 3553

	new_name := fmt.Sprintf("%s.texture.pb", name)
	fmt.Println("Gen:", new_name)
	lastfile := path.Join(baseDir, "texture", new_name)
	data, _ := proto.Marshal(&res)
	ioutil.WriteFile(lastfile, data, 0644)
}

func texture_gen_cubemap(baseDir, image, name string, mag, min, s, t, r int64) {
	segs := strings.Split(image, ",")
	{
		for _, oneimage := range segs {
			full_image_path := path.Join(baseDir, "image", oneimage)
			finfo, err := os.Lstat(full_image_path)
			if err != nil {
				return
			}
			if finfo == nil {
				return
			}
		}
	}
	var res comm.PBTexture
	res.ImageList = segs
	res.MagFilter = int32(mag)
	res.MinFilter = int32(min)
	res.WrapS = int32(s)
	res.WrapT = int32(t)
	res.WrapR = int32(r)
	res.TextureType = 34067
	new_name := fmt.Sprintf("%s.cubemap.pb", name)
	fmt.Println("Gen:", new_name)
	lastfile := path.Join(baseDir, "texture", new_name)
	data, _ := proto.Marshal(&res)
	ioutil.WriteFile(lastfile, data, 0644)
}

func texture_show(baseDir, name string) {
	new_name := fmt.Sprintf("%s.texture.pb", name)
	fullpath := path.Join(baseDir, "texture", new_name)
	data, err := ioutil.ReadFile(fullpath)
	if err != nil {
		fmt.Println(err)
		return
	}
	var res comm.PBTexture
	proto.Unmarshal(data, &res)
	jsondata, _ := json.Marshal(&res)
	fmt.Println(string(jsondata))
}

func do_texture() {
	kind := *g_texture_kind
	baseDir := *g_basedir
	image := *g_texture_image
	name := *g_texture_name
	parameter := *g_texture_parameter
	shape := *g_texture_shape
	segs := strings.Split(parameter, ",")
	if kind == "gen" {
		if shape == "texture" {
			mag, _ := strconv.ParseInt(segs[0], 0, 64)
			min, _ := strconv.ParseInt(segs[1], 0, 64)
			s, _ := strconv.ParseInt(segs[2], 0, 64)
			t, _ := strconv.ParseInt(segs[3], 0, 64)
			texture_gen_texture2d(
				baseDir,
				image,
				name,
				mag,
				min,
				s,
				t,
			)
		} else {
			mag, _ := strconv.ParseInt(segs[0], 0, 64)
			min, _ := strconv.ParseInt(segs[1], 0, 64)
			s, _ := strconv.ParseInt(segs[2], 0, 64)
			t, _ := strconv.ParseInt(segs[3], 0, 64)
			r, _ := strconv.ParseInt(segs[4], 0, 64)
			texture_gen_cubemap(
				baseDir,
				image,
				name,
				mag,
				min,
				s,
				t,
				r,
			)

		}
	} else {
		texture_show(baseDir, name)
	}
}
