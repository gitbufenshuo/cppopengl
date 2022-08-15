#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mc/csv.h>

namespace apps::csv
{
    void main_loop(GLFWwindow *window)
    {
        std::vector<float> v_data;
        std::vector<int> e_data;
        std::vector<int> s_data;
        mc::tools::CSVReader<float, int, int>::Read("../others/resource/model/cube.model", v_data, e_data, s_data);
        for (auto one : v_data)
        {
            std::cout << one << " ";
        }
        std::cout << "  --- v" << std::endl;
        //
        for (auto one : e_data)
        {
            std::cout << one << " ";
        }
        std::cout << "  --- e" << std::endl;
        //
        for (auto one : s_data)
        {
            std::cout << one << " ";
        }
        std::cout << "  --- s" << std::endl;
    }
}
