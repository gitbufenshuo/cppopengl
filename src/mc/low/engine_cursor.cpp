#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/engine.h>

namespace mc::low
{
    double Engine::s_cursor_time{};
    double Engine::s_cursor_XPOS{};
    double Engine::s_cursor_YPOS{};
    double Engine::s_c_xdiff{};
    double Engine::s_c_ydiff{};
    //
    void Engine::mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        s_cursor_time = glfwGetTime();
        s_c_xdiff = xpos - s_cursor_XPOS;
        s_c_ydiff = ypos - s_cursor_YPOS;
        s_cursor_XPOS = xpos;
        s_cursor_YPOS = ypos;
    }

}
