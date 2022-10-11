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
	Short: "给一个纹理图，生成相应的 height map 和 normal map 和 parallax map",
	Long: `生成三个文件:
1. xxx-height-map
2. xxx-normal-map
3. xxx-parallax-map`,
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
	var rawMapPath string
	var heightMapPath string
	var normalMapPath string
	var parallaxMapPath string
	if strings.HasSuffix(f.Name(), ".png") {
		m, err = png.Decode(f)
		if err != nil {
			panic("非png")
		}
	} else {
		m, err = jpeg.Decode(f)
		if err != nil {
			panic("非jpeg")
		}
	}
	rawMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_rawmap.jpg", fInfo.Name()))
	heightMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_heightmap.jpg", fInfo.Name()))
	normalMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_normalmap.jpg", fInfo.Name()))
	parallaxMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_parallaxmap.jpg", fInfo.Name()))

	fmt.Printf("%s\n", m.Bounds()) // 图片长宽

	rawMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))
	heightMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))
	parallaxMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))

	for idx := 0; idx < m.Bounds().Max.X; idx++ {
		for jdx := 0; jdx < m.Bounds().Max.Y; jdx++ {
			craw_r, craw_g, craw_b, craw_A := m.At(idx, jdx).RGBA()
			r_8, g_8, b_8, a_8 := craw_r>>8, craw_g>>8, craw_b>>8, craw_A>>8
			if idx+jdx < 100 {
				fmt.Println("- - -")
				fmt.Println(craw_r, craw_g, craw_b, craw_A)
				fmt.Println(r_8, g_8, b_8, a_8)
			}
			avg := (r_8 + g_8 + b_8) / 3
			avg_inverse := 255 - avg
			rawMap.Set(idx, jdx, color.RGBA{R: uint8(r_8), G: uint8(g_8), B: uint8(b_8), A: uint8(a_8)})
			heightMap.Set(idx, jdx, color.RGBA{R: uint8(avg), G: uint8(avg), B: uint8(avg), A: 255})
			parallaxMap.Set(idx, jdx, color.RGBA{R: uint8(avg_inverse), G: uint8(avg_inverse), B: uint8(avg_inverse), A: 255})
		}
	}
	os.Remove(rawMapPath)
	rawFile, _ := os.Create(rawMapPath)
	jpeg.Encode(rawFile, rawMap, &jpeg.Options{Quality: 10})
	//
	os.Remove(heightMapPath)
	heightFile, _ := os.Create(heightMapPath)
	jpeg.Encode(heightFile, heightMap, &jpeg.Options{Quality: 10})
	//
	os.Remove(parallaxMapPath)
	parallaxFile, _ := os.Create(parallaxMapPath)
	jpeg.Encode(parallaxFile, parallaxMap, &jpeg.Options{Quality: 10})

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
				dx = (float64(da>>8) - float64(xiao>>8)) / 255
			}
			{
				xiao, _, _, _ := heightMap.At(x, (y-1)%maxY).RGBA()
				da, _, _, _ := heightMap.At(x, (y+1)%maxY).RGBA()
				dy = (float64(da>>8) - float64(xiao>>8)) / 255
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

			normalMap.Set(x, y, color.RGBA{
				R: uint8(dx),
				G: uint8(dy),
				B: uint8(dz),
				A: 255,
			})
		}
	}
	os.Remove(normalMapPath)
	normalFile, _ := os.Create(normalMapPath)
	jpeg.Encode(normalFile, normalMap, &jpeg.Options{Quality: 10})
}
