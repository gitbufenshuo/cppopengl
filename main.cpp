#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>

#include <mc/log/log.h>

#include <game/example/example_list.h>

using entry_func = int (*)();
void reg_entry(std::unordered_map<std::string, entry_func> &entry_list)
{
    {
        entry_func one{game::example_list::function_chart::Main};
        entry_list.insert(
            std::pair(
                game::example_list::function_chart::g_name,
                one));
    }
    {
        entry_func one{game::example_list::protobuf_test::Main};
        entry_list.insert(
            std::pair(
                game::example_list::protobuf_test::g_name,
                one));
    }
    {
        entry_func one{game::example_list::DebugDraw::Main};
        entry_list.insert(
            std::pair(
                game::example_list::DebugDraw::g_name,
                one));
    }
    {
        entry_func one{game::example_list::gltf_exp::Main};
        entry_list.insert(
            std::pair(
                game::example_list::gltf_exp::g_name,
                one));
    }
    {
        entry_func one{game::example_list::cube_transform::Main};
        entry_list.insert(
            std::pair(
                game::example_list::cube_transform::g_name,
                one));
    }
    {
        entry_func one{game::example_list::gbcd::Main};
        entry_list.insert(
            std::pair(
                game::example_list::gbcd::g_name,
                one));
    }
    {
        entry_func one{game::example_list::math::Main};
        entry_list.insert(
            std::pair(
                game::example_list::math::g_name,
                one));
    }
    {
        entry_func one{game::example_list::uvt::Main};
        entry_list.insert(
            std::pair(
                game::example_list::uvt::g_name,
                one));
    }
    {
		entry_func one{game::example_list::freetype::Main};
		entry_list.insert(
			std::pair(
				game::example_list::freetype::g_name,
				one));
	}
	// placeholder
}

int main(int argc, char *argv[])
{

    mc::log::Log::Init();
    SPD_INFO("Start The Log");
    if (argc == 1)
    {
        SPD_INFO("请输入想要运行的程序");
        SPD_INFO("例如(mac): ./mc.out function_chart");
        SPD_INFO("例如(mac): ./mc.out protobuf_test");
        SPD_INFO("例如(mac): ./mc.out gltf_exp");
        SPD_INFO("例如(mac): ./mc.out cube_transform");
        SPD_INFO("例如(windows): ./mc.out.exe function_chart");
        SPD_INFO("例如(windows): ./mc.out.exe protobuf_test");
        SPD_INFO("例如(windows): ./mc.out.exe gltf_exp");
        SPD_INFO("例如(windows): ./mc.out.exe cube_transform");
        return 0;
    }
    std::unordered_map<std::string, entry_func> entry_list;
    reg_entry(entry_list);
    std::string e_name{argv[1]};
    auto func = entry_list[e_name];
    return func();
}