#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/gameobject.h>
#include <mc/camera.h>

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
        int m_width{800};
        int m_height{800};

    private:
        void update();

    public:
        Engine(int width = 800, int height = 800);
        void Run();
    };
}
#endif