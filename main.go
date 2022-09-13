package main

import (
	"fmt"
	"os"

	"gitee.com/onebook/cppopengl/bintools/stdirspec"
)

func main() {
	fmt.Println("bintools Wriiten by Golang")
	if os.Args[1] == "dirspec" {
		stdirspec.Main(os.Args[2])
	}
}
