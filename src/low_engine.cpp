#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/engine.h>
#include <mc/camera.h>

namespace
{
    void gl_context_init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw "glad_init_bad";
        }
    }
    GLFWwindow *open_new_window(int width, int height, const char *window_name)
    {
        gl_context_init();
        GLFWwindow *window = glfwCreateWindow(width, height, window_name, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw "window_bad";
        }
        glfwMakeContextCurrent(window);
        init_glad();
        return window;
    }
}

namespace mc::low
{
    Engine::Engine(int width, int height) : m_main_camera{new Camera{}}, m_width{width}, m_height{height}
    {
        m_window = open_new_window(m_width, m_height, "HelloWorld");
        std::cout << "<<<<<< Welcom to Engine >>>>>>" << std::endl;
    }

    void Engine::update()
    {
        now_time = glfwGetTime();
        std::cout << "frame interval: " << now_time - last_time << std::endl;
        last_time = now_time;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();  // shader bind
        model_0.Use(); // vao bind
        image.Use();
        shader.Uniform("ma_View", main_camera.GetViewMat());
        shader.Uniform("ma_Proj", main_camera.GetProjMat());
        {
            // logic update
            glm::sin(static_cast<float>(now_time - init_time));
            gb_1.SetLocalTranslate(glm::sin(static_cast<float>(now_time - init_time)),
                                   glm::cos(static_cast<float>(now_time - init_time)) * 10.0f,
                                   1.0f);

            shader.Uniform("lightPos", gb_1.GetWorldPos());
            shader.Uniform("lightColor", light_color);
            // gb_0.SetLocalEuler(0.0f, static_cast<float>(now_time - init_time) * 10.0f, 0.0f);
            // std::cout << "-->" << std::endl;
            // gb_0.ShowVersion();
            // gb_1.ShowVersion();
            // gb_0.Translate(0.005f, 0.0f, 0.0f);
            // gb_0.SetLocalEuler(0.0f, 0.0f, static_cast<float>(now_time - init_time) * 10.0f);
        }
        {
            // render update
            // material
            //                 vec3 ambient;
            // vec3 diffuse;
            // vec3 specular;
            // float shininess;

            shader.Uniform("material.ambient", _mate_emerald.GetAmbient());
            shader.Uniform("material.diffuse", _mate_emerald.GetDiffuse());
            shader.Uniform("material.specular", _mate_emerald.GetSpecular());
            shader.Uniform("material.shininess", _mate_emerald.GetShininess());
            // gb_0
            shader.Uniform("ma_Model", gb_0.GetWorldMat());
            glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);
            // gb_1
            shader.Uniform("ma_Model", gb_1.GetWorldMat());
            glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Engine::Run()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            update();
        }
        glfwTerminate();
    }
}