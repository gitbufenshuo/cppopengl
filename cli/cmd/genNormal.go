/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"fmt"
	"image"
	"image/color"
	"image/jpeg"
	"image/png"
	"os"
	"path"
	"strings"

	"github.com/spf13/cobra"
)

var (
	gFile   *string
	gOutDir *string
)

// genNormalCmd represents the genNormal command
var genNormalCmd = &cobra.Command{
	Use:   "genNormal",
	Short: "给一个纹理图，生成相应的 height map 和 normal map",
	Long: `生成两个文件:
1. xxx-height-map
2. xxx-normal-map`,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("genNormal 正在执行")
		fmt.Println("file", *gFile)
		fmt.Println("outDir", *gOutDir)
		doyewu()
	},
}

func init() {
	rootCmd.AddCommand(genNormalCmd)
	gFile = genNormalCmd.Flags().StringP("file", "f", "", "指定输入图片")
	genNormalCmd.MarkFlagRequired("file")
	gOutDir = genNormalCmd.Flags().StringP("outdir", "o", ".", "指定输出路径")
}

func doyewu() {
	var err error
	var m image.Image
	var f *os.File
	f, err = os.Open(*gFile)
	if err != nil {
		panic(err)
	}
	fInfo, _ := f.Stat()
	fInfo.Name()

	fmt.Println("FileName", fInfo.Name())
	var heightMapPath string
	var normalMapPath string
	var pngma bool
	if strings.HasSuffix(f.Name(), ".png") {
		m, err = png.Decode(f)
		if err != nil {
			panic("非png")
		}
		heightMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_heightmap.png", fInfo.Name()))
		normalMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_normalmap.png", fInfo.Name()))
		pngma = true
	} else {
		m, err = jpeg.Decode(f)
		if err != nil {
			panic("非jpeg")
		}
		heightMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_heightmap.jpeg", fInfo.Name()))
		normalMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_normalmap.jpeg", fInfo.Name()))
	}
	fmt.Printf("%s\n", m.Bounds()) // 图片长宽
	heightMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))
	for idx := 0; idx < m.Bounds().Max.X; idx++ {
		for jdx := 0; jdx < m.Bounds().Max.Y; jdx++ {
			craw_r, craw_g, craw_b, _ := m.At(idx, jdx).RGBA()
			avg := (craw_r + craw_g + craw_b) / 3
			heightMap.SetRGBA(idx, jdx, color.RGBA{R: uint8(avg), G: uint8(avg), B: uint8(avg)})
		}
	}
	os.Remove(heightMapPath)
	heightFile, _ := os.Create(heightMapPath)
	if pngma {
		png.Encode(heightFile, heightMap)
	} else {
		jpeg.Encode(heightFile, heightMap, nil)
	}
	//
	normalMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))
	maxX, maxY := m.Bounds().Max.X, m.Bounds().Max.Y
	for x := 0; x < m.Bounds().Max.X; x++ {
		for y := 0; y < m.Bounds().Max.Y; y++ {
			// dx
			var dx, dy, dz float64
			dz = 1
			{
				xiao, _, _, _ := heightMap.At((x-1)%maxX, y).RGBA()
				da, _, _, _ := heightMap.At((x+1)%maxX, y).RGBA()
				dx = (float64(da) - float64(xiao)) / 255
			}
			{
				xiao, _, _, _ := heightMap.At(x, (y-1)%maxY).RGBA()
				da, _, _, _ := heightMap.At(x, (y+1)%maxY).RGBA()
				dy = (float64(da) - float64(xiao)) / 255
			}
			dx = -dx
			dy = -dy

			dx *= 255
			dx += 255
			dx /= 2

			dy *= 255
			dy += 255
			dy /= 2

			dz *= 255
			dz += 255
			dz /= 2

			normalMap.SetRGBA(x, y, color.RGBA{
				R: uint8(dx),
				G: uint8(dy),
				B: uint8(dz),
			})
		}
	}
	os.Remove(normalMapPath)
	normalFile, _ := os.Create(normalMapPath)
	if pngma {
		png.Encode(normalFile, normalMap)
	} else {
		jpeg.Encode(normalFile, normalMap, nil)
	}
}
