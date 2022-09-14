#include <iostream>
#include <mc/app.h>

namespace mc
{
    App::App(GLFWwindow *window, const char *name) : m_window{window}, m_name{name}
    {
        asd;
    }
    App::~App()
    {
    }
    void App::Run(RunFunc run_func)
    {
        if (!run_func)
        {
            throw "run_func is null";
        }
        std::cout << m_name << " is running" << std::endl;
        run_func(m_window);
    }
}