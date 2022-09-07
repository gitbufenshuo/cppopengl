#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>

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
        entry_func one{game::example_list::gltf_exp::Main};
        entry_list.insert(
            std::pair(
                game::example_list::gltf_exp::g_name,
                one));
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "请输入想要运行的程序\n"
                  << "例如(mac): ./mc.out function_chart" << std::endl
                  << "例如(mac): ./mc.out protobuf_test" << std::endl
                  << "例如(mac): ./mc.out gltf_exp" << std::endl
                  << "例如(windows): ./mc.out.exe function_chart" << std::endl
                  << "例如(windows): ./mc.out.exe protobuf_test" << std::endl
                  << "例如(windows): ./mc.out.exe gltf_exp" << std::endl;
        return 0;
    }
    std::unordered_map<std::string, entry_func> entry_list;
    reg_entry(entry_list);
    std::string e_name{argv[1]};
    auto func = entry_list[e_name];
    return func();
}