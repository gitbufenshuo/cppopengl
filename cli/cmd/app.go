/*
Copyright © 2022 NAME HERE <EMAIL ADDRESS>

*/
package cmd

import (
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strings"

	"github.com/spf13/cobra"
)

var (
	g_app_name *string
)

// appCmd represents the app command
var appCmd = &cobra.Command{
	Use:   "app",
	Short: "生成一个新的example",
	Long:  ``,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("app called")
		do_app()
	},
}

func init() {
	rootCmd.AddCommand(appCmd)
	//
	g_app_name = appCmd.Flags().String("name", "default", "name")
}

func do_app() {
	example_lish_h_path := "others/include/game/example/example_list.h"
	data, _ := ioutil.ReadFile(example_lish_h_path)
	core_string := fmt.Sprintf("example_list::%s", *g_app_name)
	if strings.Contains(string(data), core_string) {
		fmt.Println(example_lish_h_path, "已经含有同名app")
		return
	}
	//
	example_list_h_func(*g_app_name)
	main_cpp_func(*g_app_name)
	exapmle_cpp_func(*g_app_name)

}

/*
	生成一个新的 example
*/
// ./bintools app name

var example_main_cpp = `#include <iostream>
#include <string>
#include <fstream>

// mc low headers
#include <mc/engine.h>

// log
#include <mc/log/log.h>

namespace
{
    void registArtLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ArtLogicPhong::Register(am.GetARF());
    }
    void registActLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ActLogicCamera::Register(am.GetACF());
    }

}

namespace game::example_list::${NAME}
{
    int Main()
    {
        mc::low::Engine gogogo{800, 800, "Hello ${NAME}"};
        registArtLogic(gogogo);
        registActLogic(gogogo);
        gogogo.LoadAssetAndCreate("gogogo.pb.data", false);
        gogogo.Run();
        return 0;
    }
}
`

var main_cpp = `{
		entry_func one{game::example_list::${NAME}::Main};
		entry_list.insert(
			std::pair(
				game::example_list::${NAME}::g_name,
				one));
	}
	// placeholder`

var example_list_h = `namespace game::example_list::${NAME}
{
    const std::string g_name{"${NAME}"};
    int Main();
}
// placeholder
`

func example_list_h_func(name string) {
	example_lish_h_path := "others/include/game/example/example_list.h"
	data, _ := ioutil.ReadFile(example_lish_h_path)
	newthing := strings.ReplaceAll(example_list_h, "${NAME}", name)
	lastthing := strings.ReplaceAll(string(data), "// placeholder", newthing)
	os.Remove(example_lish_h_path)
	ioutil.WriteFile(example_lish_h_path, []byte(lastthing), 0644)
}

func main_cpp_func(name string) {
	main_cpp_path := "main.cpp"
	data, _ := ioutil.ReadFile(main_cpp_path)
	newthing := strings.ReplaceAll(main_cpp, "${NAME}", name)
	lastthing := strings.ReplaceAll(string(data), "// placeholder", newthing)
	os.Remove(main_cpp_path)
	ioutil.WriteFile(main_cpp_path, []byte(lastthing), 0644)
}

func exapmle_cpp_func(name string) {
	newdir := path.Join("src", "example", name)
	os.MkdirAll(newdir, 0755)
	//
	lastthing := strings.ReplaceAll(example_main_cpp, "${NAME}", name)
	os.RemoveAll(path.Join(newdir, "main.cpp"))
	ioutil.WriteFile(path.Join(newdir, "main.cpp"), []byte(lastthing), 0644)
}

func theap() {

	// heap.Init()

}
