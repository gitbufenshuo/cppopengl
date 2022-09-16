package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"

	"gitee.com/onebook/cppopengl/bintools/start"
	"gitee.com/onebook/cppopengl/bintools/stdirspec"
	"gitee.com/onebook/cppopengl/bintools/stmaterial"
	"gitee.com/onebook/cppopengl/bintools/stmodel"
	"gitee.com/onebook/cppopengl/bintools/stscene"
	"gitee.com/onebook/cppopengl/bintools/stshader"
	"gitee.com/onebook/cppopengl/bintools/sttexture"
)

func main() {
	fmt.Println("bintools Wriiten by Golang")
	rand.Seed(time.Now().Unix())
	if os.Args[1] == "dirspec" {
		stdirspec.Main(os.Args[2])
		return
	}
	if os.Args[1] == "texture" {
		sttexture.Main()
		return
	}
	if os.Args[1] == "art" {
		start.Main()
		return
	}
	if os.Args[1] == "model" {
		stmodel.Main()
		return
	}
	if os.Args[1] == "shader" {
		stshader.Main()
		return
	}
	if os.Args[1] == "material" {
		stmaterial.Main()
		return
	}
	if os.Args[1] == "scene" {
		stscene.Main()
		return
	}

}
