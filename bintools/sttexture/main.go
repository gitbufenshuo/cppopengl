package sttexture

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strconv"
	"time"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

/*
	texture
	1. gen baseDir image mag min s t
	2. show baseDir image
	eg:
	gen baseDir one.png 9729 9987 10497
	show baseDir
*/

func _gen(baseDir, image string, mag, min, s, t int) {
	var res comm.PBTexture
	res.Image = path.Join(baseDir, "image", image)
	{
		finfo, err := os.Lstat(res.Image)
		if err != nil {
			return
		}
		if finfo == nil {
			return
		}
	}
	res.MagFilter = int32(mag)
	res.MinFilter = int32(min)
	res.WrapS = int32(s)
	res.WrapT = int32(t)
	lastfile := path.Join(baseDir, "texture", fmt.Sprintf("%s%d.texture.pb", image, time.Now().UnixMilli()%5))
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
		mag, _ := strconv.Atoi(os.Args[5])
		min, _ := strconv.Atoi(os.Args[6])
		s, _ := strconv.Atoi(os.Args[7])
		t, _ := strconv.Atoi(os.Args[8])
		_gen(
			baseDir,
			image,
			mag,
			min,
			s,
			t,
		)
	} else {
		_show(baseDir, image)
	}
}
