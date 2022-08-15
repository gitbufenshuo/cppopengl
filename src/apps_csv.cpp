#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mc/csv.h>

namespace apps::csv
{
    void main_loop(GLFWwindow *window)
    {
        std::vector<float> data;
        mc::tools::CSVReader<float>::Read("../others/resource/model/cube.model", data);
        for (auto one : data)
        {
            std::cout << one << std::endl;
        }
    }
}
