#include <iostream>
#include <utility>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/engine.h>
#include <mc/gameobject.h>
#include <mc/camera.h>

namespace
{
    unsigned int frame_count{0};
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
    Engine::Engine(int width, int height, const char *name) : m_main_camera{new Camera{}}, m_width{width}, m_height{height}, m_am{std::make_shared<mc::asset::AssetManager>()}
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
        // 遍历 m_append 这是即将加入 egine 的 gameobject
        for (auto one_gb : m_append)
        {
            m_gameobjects.insert(std::pair{one_gb->GetID(), std::unique_ptr<GameObject>{one_gb}});
        }
        m_append.clear();
        // 遍历各个 gameobject，执行 logicsupport 上的 Update 函数
        for (auto &pair : m_gameobjects)
        {
            auto _gb = pair.second.get();
            if (_gb->GetDeleted())
            {
                // 如果已经删了，就跳过
                continue;
            }
            _gb->Update(delta_time);
        }
        // 将 gameobject 从 engine 中删掉
        for (auto one_gb_id : m_deleted_id)
        {
            m_gameobjects.erase(one_gb_id);
        }
        // 清空列表
        m_deleted_id.resize(0);
    }
    void Engine::standard_render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // 遍历各个 gameobject, 画出来
        for (auto &pair : m_gameobjects)
        {
            auto _gb = pair.second.get();
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
            auto art_logic{_material->GetArtLogic()};
            art_logic->PostUniform(this, _gb);
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
            _gb->AfterRenderUpdate(delta_time);
        }
        // draw skybox
        glDepthFunc(GL_LEQUAL);
        m_main_camera->DrawSkybox();
        glDepthFunc(GL_LESS);
    }
    void Engine::after_render_logic()
    {
    }

    void Engine::update()
    {
        logic_update();
        standard_render();
        after_render_logic();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Engine::Run()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            ++frame_count;
            update();
        }
        glfwTerminate();
    }
    void Engine::AddGameobject(GameObject *game_object)
    {
        game_object->SetID(m_next_id++);
        m_append.push_back(game_object);
        // m_gameobjects.insert(std::pair{game_object->GetID(), std::unique_ptr<GameObject>{game_object}});
        std::cout << "User [Engine::AddGameobject] " << game_object->GetID() << std::endl;
    }

    void Engine::markGBDel(GameObject *game_object)
    {
        m_deleted_id.push_back(game_object->GetID());
        game_object->MarkDeleted();
        //
        auto tr{game_object->GetTransform()};
        for (int index = 0; index < tr->SubSize(); ++index)
        {
            auto sub_tr{tr->Sub(index)};
            markGBDel(sub_tr->GetGB());
        }
    }

    void Engine::DelGameobject(GameObject *game_object)
    {
        std::cout << "User [Engine::DelGameobject] " << game_object->GetID() << std::endl;
        // 先从节点树(Transform)上拆除此 gb
        auto tr{game_object->GetTransform()};
        tr->SetUpper(nullptr);
        // 遍历此 tr 的下级, 将本身和所有下级的gb 都标记成 deleted
        markGBDel(game_object);
    }
    int Engine::GameObjectSize()
    {
        return m_gameobjects.size();
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
    std::shared_ptr<mc::asset::AssetManager> Engine::GetAM()
    {
        return m_am;
    }
}