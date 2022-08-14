#ifndef APP_H
#define APP_H

#include <string>

#include <GLFW/glfw3.h>

namespace mc
{
    class App
    {
        GLFWwindow *m_window;
        const std::string m_name;

    public:
        using RunFunc = void (*)(GLFWwindow *m_window);
        App(GLFWwindow *, const char *);
        ~App();
        void Run(RunFunc);
    };
}

#endif