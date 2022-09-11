#include <iostream>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/engine.h>
#include <mc/gameobject.h>
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
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        return window;
    }
    void KeyCallback(GLFWwindow *, int key, int scancode, int action, int mods)
    {
        float now_time = static_cast<float>(glfwGetTime());
        mc::low::Engine::s_keyinput(now_time, key, scancode, action, mods);
    }
}

namespace mc::low
{
    Engine::Engine(int width, int height, const char *name) : m_main_camera{new Camera{}}, m_width{width}, m_height{height}
    {
        m_window = open_new_window(m_width, m_height, name);
        now_time = glfwGetTime();
        last_time = now_time;
        init_time = now_time;
        glfwSetCursorPosCallback(m_window, mouse_callback);
        // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(m_window, KeyCallback);
        std::cout << "<<<<<< Welcom to Engine >>>>>>" << std::endl;
    }
    void Engine::Setup(InitFunc p)
    {
        p(m_window);
    }
    void Engine::logic_update()
    {
        now_time = glfwGetTime();
        if (now_time - s_cursor_time > 0.01)
        {
            s_c_xdiff = 0.0;
            s_c_ydiff = 0.0;
        }
        delta_time = now_time - last_time;
        // std::cout << "frame interval: " << delta_time << " framerate: " << 1.0 / (delta_time) << std::endl;
        last_time = now_time;
        // 遍历各个 gameobject，执行 logicsupport 上的 Update 函数
        for (auto &pair : m_gameobjects)
        {
            auto _gb = pair.second;
            _gb->Update(delta_time);
        }
    }
    void Engine::standard_render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 遍历各个 gameobject, 画出来
        for (auto &pair : m_gameobjects)
        {
            auto _gb = pair.second;
            auto mr = pair.second->GetMeshRender();
            if (!mr)
            {
                // 没有 mesh render, 相当于不用渲染
                continue;
            }
            auto _material = mr->GetMaterial();
            if (!_material)
            {
                // 没有 材质，说明这个mesh render 设置不完整
                continue;
            }
            auto _mesh_filter = _gb->GetMeshFilter();
            if (!_mesh_filter)
            {
                // 没有模型
                continue;
            }
            // material tasks
            _material->PostUniform(this, _gb);
            _gb->BeforeRenderUpdate(delta_time);
            // 遍历每一个 primitive model
            {
                int model_size = _mesh_filter->modelsize();
                for (int index = 0; index < model_size; ++index)
                {
                    auto _model = _mesh_filter->GetModel(index);
                    _model->Use();
                    glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), _model->GetEBOType(), 0);
                }
            }
            // 在画之前，遍历 logic_support
            // 画
            // 在画之后，遍历 logic_support
            _gb->AfterRenderUpdate(delta_time);
        }
    }
    void Engine::update()
    {
        logic_update();
        standard_render();

        glfwSwapBuffers(m_window);
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
    void Engine::AddGameobject(GameObject *game_object)
    {
        game_object->SetID(m_next_id++);
        m_gameobjects.insert(std::pair{game_object->GetID(), game_object});
        std::cout << "[Engine::AddGameobject] " << game_object->GetID() << std::endl;
    }
    // static
    // static for gl op
    void Engine::S_GL_EnableFaceCull(bool zhi)
    {
        if (zhi)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
    }
}