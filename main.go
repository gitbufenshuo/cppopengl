package main

import (
	"fmt"
	"os"

	"gitee.com/onebook/cppopengl/bintools/stgltf"
)

func main() {
	fmt.Println("bintools Wriiten by Golang")
	if os.Args[1] == "gltf" {
		stgltf.Main(os.Args[2], os.Args[3], os.Args[4])
	}
}
