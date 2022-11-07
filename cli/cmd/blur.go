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
	g_blur_outdir *string
	g_blur_input  *string
)

// blurCmd represents the blur command
var blurCmd = &cobra.Command{
	Use:   "blur",
	Short: "虚化图片",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("blur called")
		do_blur()
	},
}

func init() {
	rootCmd.AddCommand(blurCmd)
	//
	g_blur_outdir = blurCmd.Flags().String("outdir", "", "指定输出目录")
	g_blur_input = blurCmd.Flags().String("input", "", "指定输入图片")
}

func do_blur() {
	var err error
	var m image.Image
	var f *os.File
	f, err = os.Open(*g_blur_input)
	if err != nil {
		panic(err)
	}
	fInfo, _ := f.Stat()
	fInfo.Name()

	fmt.Println("FileName", fInfo.Name())
	var rawMapPath string

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
	rawMapPath = path.Join(*gOutDir, fmt.Sprintf("%s_blur.png", fInfo.Name()))

	fmt.Printf("%s\n", m.Bounds()) // 图片长宽

	rawMap := image.NewRGBA(image.Rect(0, 0, m.Bounds().Max.X, m.Bounds().Max.Y))

	for idx := 0; idx < m.Bounds().Max.X; idx++ {
		for jdx := 0; jdx < m.Bounds().Max.Y; jdx++ {
			rawMap.Set(idx, jdx, avg(m, idx, jdx, m.Bounds().Max.X, m.Bounds().Max.Y))
		}
	}
	os.Remove(rawMapPath)
	rawFile, _ := os.Create(rawMapPath)
	png.Encode(rawFile, rawMap)
}

func avg(source image.Image, centerx, centery int, width, height int) color.RGBA {
	var total_r, total_g, total_b float64
	offset := make([]int, 51)
	weight := make([]float64, 51)
	for idx := range offset {
		offset[idx] = idx - len(offset)/2
	}
	var prev float64 = 0.05
	for idx := len(offset) / 2; idx < len(offset); idx++ {
		weight[idx] = prev * 9 * 0.1
		prev = weight[idx]
	}
	prev = 0.05
	for idx := len(offset) / 2; idx >= 0; idx-- {
		weight[idx] = prev * 9 * 0.1
		prev = weight[idx]
	}
	var rx, ry int
	for x := 0; x < len(offset); x++ {
		for y := 0; y < len(offset); y++ {
			rx = centerx + offset[x]
			if rx > width {
				rx = rx % width
			}
			if rx < 0 {
				rx = width + rx
			}
			ry = centery + offset[y]
			if ry > height {
				ry = ry % height
			}
			if ry < 0 {
				ry = height + ry
			}
			//
			craw_r, craw_g, craw_b, _ := source.At(rx, ry).RGBA()
			total_r += float64(craw_r>>8) * weight[x] * weight[y]
			total_g += float64(craw_g>>8) * weight[x] * weight[y]
			total_b += float64(craw_b>>8) * weight[x] * weight[y]
		}
	}
	return color.RGBA{R: uint8(total_r), G: uint8(total_g), B: uint8(total_b), A: uint8(255)}
}
