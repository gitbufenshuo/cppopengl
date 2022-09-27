namespace mc::low
{
    class Engine;
}
#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <mc/gameobject.h>
#include <mc/camera.h>
#include <mc/keyinputsystem.h>

// comm headers
#include <mc/comm/pbdirspec.pb.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/light.h>

namespace mc::low
{
    using InitFunc = void (*)(GLFWwindow *window);
    class Engine
    {
        int m_next_id{1};
        std::unordered_map<int, std::unique_ptr<GameObject>> m_gameobjects;
        GLFWwindow *m_window;
        Camera *m_main_camera;
        double now_time{};
        double last_time{};
        double init_time{};
        double delta_time{};
        int m_width{800};
        int m_height{800};

        // light source
        glm::vec3 m_light_color{1.0f, 1.0f, 1.0f};
        glm::vec3 m_light_pos{-60.0f, 60.0f, -60.0f};
        std::vector<std::shared_ptr<mc::asset::Light>> m_light_list;

        // deleted id
        std::vector<int> m_deleted_id;
        std::vector<GameObject *> m_append; // 新进来的gameobject
        // asset
        std::shared_ptr<mc::asset::AssetManager> m_am;

    public:
        // static
        static double s_cursor_time;
        static double s_cursor_XPOS;
        static double s_cursor_YPOS;
        static double s_c_xdiff;
        static double s_c_ydiff;
        static KeyInputSystem s_keyinput;                                         // 键盘事件管理器
        void LoadAssetAndCreate(const char *file_path, bool createScene = false); // 从文件中加载所有的资源

    private:
        void markGBDel(GameObject *gb);
        void update();
        void logic_update();
        void after_render_logic();
        void standard_render(); // 普通渲染 gameobject
        void outline_render();  // 绘制轮廓
        void draw_plain();
        void shadow_generate(); // 生成 shadow map
        void draw_skybox();     // 绘制天空盒子
        void loadAsset(const char *file_path, mc::comm::PBDirSpec &pb_data);

    public:
        std::shared_ptr<mc::asset::AssetManager> GetAM();
        Camera *GetCamera()
        {
            return m_main_camera;
        }
        void Run();

        void AddGameobject(GameObject *gb);
        void DelGameobject(GameObject *gb); // 删除某个gb
        int GameObjectSize();

        std::shared_ptr<mc::asset::Light> GetLight(int index)
        {
            return m_light_list[index];
        }
        void AddLight(std::shared_ptr<mc::asset::Light> light)
        {
            m_light_list.push_back(light);
        }

        int LightSize()
        {
            return m_light_list.size();
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
        void Setup(InitFunc p);

    public:
        static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        // gl 相关操作，这样用户代码可以不用引用 gl 相关header
        static void S_GL_EnableFaceCull(bool zhi); // 是否打开 face cull
    };
}
#endif