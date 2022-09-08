package stgltf

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strings"

	"gitee.com/onebook/cppopengl/bintools/mc/comm"
	"google.golang.org/protobuf/proto"
)

type GLTF struct {
	Scene  int `json:"scene"`
	Scenes []struct {
		Nodes []int `json:"nodes"`
	} `json:"scenes"`
	Nodes []struct {
		Mesh int `json:"mesh"`
	} `json:"nodes"`
	Meshes []struct {
		Primitives []struct {
			Attributes struct {
				Position  int `json:"POSITION"`
				Normal    int `json:"NORMAL"`
				Texcoord0 int `json:"TEXCOORD_0"`
			} `json:"attributes"`
			Indices int `json:"indices"`
		} `json:"primitives"`
	} `json:"meshes"`
	Textures []struct {
		Sampler int `json:"sampler"`
		Source  int `json:"source"`
	} `json:"textures"`
	Images []struct {
		URI string `json:"uri"`
	} `json:"images"`
	Samplers []struct {
		MagFilter int `json:"magFilter"`
		MinFilter int `json:"minFilter"`
		WrapS     int `json:"wrapS"`
		WrapT     int `json:"wrapT"`
	} `json:"samplers"`
	Buffers []struct {
		URI        string `json:"uri"`
		ByteLength int    `json:"byteLength"`
	} `json:"buffers"`
	BufferViews []struct {
		Buffer     int `json:"buffer"`
		ByteOffset int `json:"byteOffset"`
		ByteLength int `json:"byteLength"`
		Target     int `json:"target"`
		ByteStride int `json:"byteStride,omitempty"`
	} `json:"bufferViews"`
	Accessors []struct {
		BufferView    int    `json:"bufferView"`
		ByteOffset    int    `json:"byteOffset"`
		ComponentType int    `json:"componentType"`
		Count         int    `json:"count"`
		Type          string `json:"type"`
		Max           []int  `json:"max"`
		Min           []int  `json:"min"`
	} `json:"accessors"`
	Asset struct {
		Version string `json:"version"`
	} `json:"asset"`
}

// 解析 gltf(json)
// 转成 proto bytes(二进制)
func gltf2proto(input []byte) []byte {
	var gltfP comm.GLTF
	if jsonerr := json.Unmarshal(input, &gltfP); jsonerr != nil {
		panic("非法的gltf文件" + jsonerr.Error())
	}

	//
	protoBytes, err := proto.Marshal(&gltfP)
	if err != nil {
		panic(err)
	}
	return protoBytes
}

// 解析 proto bytes(二进制)
// 转成 gltf(json)
func proto2gltf(input []byte) []byte {
	return nil
}

func Main(dir string, inputFile string, outdir string) {
	fmt.Println("gltf convert tools -> ", dir, inputFile)
	if dir == "g2p" {
		// ./bintools.out gltf g2p ./resource/gltf/minimal.json ./resource/gltf
		data, _ := ioutil.ReadFile(inputFile)
		pbdata := gltf2proto(data)
		segs := strings.Split(inputFile, "/")
		filename := fmt.Sprintf("%s.gltf.pb", segs[len(segs)-1])
		outFilePath := path.Join(outdir, filename)
		os.Remove(outFilePath)
		fmt.Println("outdir", outFilePath)
		ioutil.WriteFile(outFilePath, pbdata, 0644)
	} else {
	}
}
