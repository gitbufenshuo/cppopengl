package main

import (
	"fmt"
	"os"

	"gitee.com/onebook/cppopengl/bintools/stdirspec"
	"gitee.com/onebook/cppopengl/bintools/sttexture"
)

func main() {
	fmt.Println("bintools Wriiten by Golang")
	if os.Args[1] == "dirspec" {
		stdirspec.Main(os.Args[2])
		return
	}
	if os.Args[1] == "texture" {
		sttexture.Main()
		return
	}
}
