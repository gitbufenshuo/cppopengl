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
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "请输入想要运行的程序\n"
                  << "例如: ./mc.out function_chart" << std::endl;
        return 0;
    }
    std::unordered_map<std::string, entry_func> entry_list;
    reg_entry(entry_list);
    std::string e_name{argv[1]};
    auto func = entry_list[e_name];
    return func();
}