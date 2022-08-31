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
}

namespace mc::low
{
    Engine::Engine(int width, int height, const char *name) : m_main_camera{new Camera{}}, m_width{width}, m_height{height}
    {
        m_window = open_new_window(m_width, m_height, name);
        now_time = glfwGetTime();
        last_time = now_time;
        init_time = now_time;
        std::cout << "<<<<<< Welcom to Engine >>>>>>" << std::endl;
    }
    void Engine::logic_update()
    {
        now_time = glfwGetTime();
        double delta_time = now_time - last_time;
        std::cout << "frame interval: " << delta_time << " framerate: " << 1.0 / (delta_time) << std::endl;
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
            // model
            auto _model = _mesh_filter->GetModel();
            _model->Use();
            // shader
            auto _shader = _material->GetShader();
            _shader->Use();
            // texture
            auto _texture = _material->GetTexture();
            _texture->Use();
            // 传一些 uniform
            {
                _shader->Uniform("ma_View", m_main_camera->GetViewMat());
                _shader->Uniform("ma_Proj", m_main_camera->GetProjMat());
                _shader->Uniform("lightPos", m_light_pos);
                _shader->Uniform("lightColor", m_light_color);
            }
            {
                _shader->Uniform("material.ambient", _material->GetAmbient());
                _shader->Uniform("material.diffuse", _material->GetDiffuse());
                _shader->Uniform("material.specular", _material->GetSpecular());
                _shader->Uniform("material.shininess", _material->GetShininess());
            }
            {
                _shader->Uniform("ma_Model", _gb->GetTransform()->GetWorldMat());
            }
            // 画
            glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), GL_UNSIGNED_INT, 0);
        }
    }
    void Engine::update()
    {
        logic_update();
        standard_render();
        //
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
}