#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/app.h>
#include <mc/apps.h>

void show_hello();

void gl_context_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
GLFWwindow *open_new_window()
{
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "window_bad";
    }
    glfwMakeContextCurrent(window);
    return window;
}
void init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw "glad_init_bad";
    }
}

int main()
{
    show_hello();
    gl_context_init();
    auto _window = open_new_window();
    init_glad();
    //
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    mc::App ins_init{_window, "init"};
    mc::App ins_vao{_window, "vao"};
    mc::App ins_math{_window, "glm"};
    mc::App ins_xyzw{_window, "xyzw"};
    mc::App ins_csv{_window, "csv"};
    ins_csv.Run(apps::csv::main_loop);
}
