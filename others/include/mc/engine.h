#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <mc/gltf/buffer.h>

#include <mc/gameobject.h>
#include <mc/camera.h>
#include <mc/shader_store.h>
#include <mc/model_store.h>
#include <mc/texture_store.h>
#include <mc/material_store.h>
#include <mc/keyinputsystem.h>

namespace mc::low
{
    class Engine
    {
        int m_next_id{1};
        std::unordered_map<int, GameObject *> m_gameobjects;
        GLFWwindow *m_window;
        Camera *m_main_camera;
        double now_time{};
        double last_time{};
        double init_time{};
        double delta_time{};
        int m_width{800};
        int m_height{800};
        glm::vec3 m_light_color{1.0f, 1.0f, 1.0f};
        glm::vec3 m_light_pos{0.0f, 0.0f, 0.0f};
        ShaderStore m_shader_store;     // 这东西不用指针
        ModelStore m_model_store;       // 这东西不用指针
        TextureStore m_texture_store;   // 这东西不用指针
        MaterialStore m_material_store; // 这东西不用指针

    public:
        // static
        static double s_cursor_time;
        static double s_cursor_XPOS;
        static double s_cursor_YPOS;
        static double s_c_xdiff;
        static double s_c_ydiff;
        static KeyInputSystem s_keyinput; // 键盘事件管理器

    private:
        void update();
        void logic_update();
        void standard_render();

    public:
        Camera *GetCamera()
        {
            return m_main_camera;
        }
        void Run();
        void LoadFromGLTF(const mc::gltf::GLTF &gltf);
        void AddGameobject(GameObject *gb);
        ShaderStore &GetShaderStore()
        {
            return m_shader_store;
        }
        ModelStore &GetModelStore()
        {
            return m_model_store;
        }
        TextureStore &GetTextureStore()
        {
            return m_texture_store;
        }
        MaterialStore &GetMaterialStore()
        {
            return m_material_store;
        }

        void SetLightColor(glm::vec3 color)
        {
            m_light_color = color;
        }
        glm::vec3 GetLightColor()
        {
            return m_light_color;
        }
        void SetLightPos(glm::vec3 pos)
        {
            m_light_pos = pos;
        }
        glm::vec3 GetLightPos()
        {
            return m_light_pos;
        }

    public:
        Engine(int width = 800, int height = 800, const char *name = "HelloOpenGL");

    public:
        static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        // gl 相关操作，这样用户代码可以不用引用 gl 相关header
        static void S_GL_EnableFaceCull(bool zhi); // 是否打开 face cull
    };
}
#endif