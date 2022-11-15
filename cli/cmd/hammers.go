/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"fmt"

	"github.com/spf13/cobra"
)

// hammersCmd represents the hammers command
var hammersCmd = &cobra.Command{
	Use:   "hammers",
	Short: "打印hammersley序列观察用",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("hammers called")
		do_hammers()
	},
}

func init() {
	rootCmd.AddCommand(hammersCmd)
}

func RadicalInverse_VdC(bits uint32) float32 {
	bits = (bits << 16) | (bits >> 16)
	bits = ((bits & 0x55555555) << 1) | ((bits & 0xAAAAAAAA) >> 1)
	bits = ((bits & 0x33333333) << 2) | ((bits & 0xCCCCCCCC) >> 2)
	bits = ((bits & 0x0F0F0F0F) << 4) | ((bits & 0xF0F0F0F0) >> 4)
	bits = ((bits & 0x00FF00FF) << 8) | ((bits & 0xFF00FF00) >> 8)
	return float32(bits) * 2.3283064365386963e-10 // / 0x100000000
}

type vec2 struct {
	x, y float32
}

// ----------------------------------------------------------------------------
func Hammersley(i, N uint32) vec2 {
	return vec2{
		float32(i) / float32(N),
		RadicalInverse_VdC(i),
	}
}
func do_hammers() {
	for i := uint32(0); i < 100; i++ {
		v2 := Hammersley(i, 100)
		fmt.Println(v2)
	}
}
