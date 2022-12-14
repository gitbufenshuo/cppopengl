package sttexture

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strconv"
	"strings"
	"time"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

/*
	texture
	1. gen baseDir image mag min s t r
	2. show baseDir image
	eg:
	gen baseDir one.png 9729 9987 10497
	show baseDir
*/

func _gen_texture2d(baseDir, image string, mag, min, s, t int) {
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

	new_name := fmt.Sprintf("%s%d.texture.pb", image, time.Now().UnixMilli()%5)
	fmt.Println("Gen:", new_name)
	lastfile := path.Join(baseDir, "texture", new_name)
	data, _ := proto.Marshal(&res)
	ioutil.WriteFile(lastfile, data, 0644)
}

func _gen_cubemap(baseDir, image string, mag, min, s, t, r int) {
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
	new_name := fmt.Sprintf("%s%d.cubemap.pb", image, time.Now().UnixMilli()%5)
	fmt.Println("Gen:", new_name)
	lastfile := path.Join(baseDir, "texture", new_name)
	data, _ := proto.Marshal(&res)
	ioutil.WriteFile(lastfile, data, 0644)
}

func _show(baseDir, texture string) {
	fullpath := path.Join(baseDir, "texture", texture)
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

func Main() {
	kind := os.Args[2]
	baseDir := os.Args[3]
	image := os.Args[4]
	if kind == "gen" {
		if len(os.Args) == 9 {
			mag, _ := strconv.Atoi(os.Args[5])
			min, _ := strconv.Atoi(os.Args[6])
			s, _ := strconv.Atoi(os.Args[7])
			t, _ := strconv.Atoi(os.Args[8])
			_gen_texture2d(
				baseDir,
				image,
				mag,
				min,
				s,
				t,
			)
		} else {
			mag, _ := strconv.Atoi(os.Args[5])
			min, _ := strconv.Atoi(os.Args[6])
			s, _ := strconv.Atoi(os.Args[7])
			t, _ := strconv.Atoi(os.Args[8])
			r, _ := strconv.Atoi(os.Args[9])
			_gen_cubemap(
				baseDir,
				image,
				mag,
				min,
				s,
				t,
				r,
			)

		}
	} else {
		_show(baseDir, image)
	}
}
