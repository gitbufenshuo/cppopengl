#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/keyinputsystem.h>

namespace mc::low
{
    // constructors
    KeyInputSystem::KeyInputSystem()
    {
        m_key_list.resize(300);
    }
    KeyInputSystem::CircleKeyAction::CircleKeyAction() : m_index{1}
    {
        m_list.resize(10); // 每个键记录十个动作
        for (auto &one : m_list)
        {
            one.action = -1; // 无效值
        }
    }
    void KeyInputSystem::CircleKeyAction::NewAction(float time, int action)
    {
        m_list[m_index].time = time;
        m_list[m_index].action = action;
        ++m_index;
        m_index %= static_cast<int>(m_list.size());
    }
    bool KeyInputSystem::CircleKeyAction::KeyStateDown()
    {
        int cur_index = m_index - 1;
        cur_index = cur_index < 0 ? m_list.size() - 1 : cur_index;
        switch (m_list[cur_index].action)
        {
        case GLFW_PRESS:
        case GLFW_REPEAT:
            return true;
            break;
        default:
            break;
        }
        return false;
    }

    // overload operators
    void KeyInputSystem::operator()(float now_time, int key, int scancode, int action, int mods)
    {
        // std::cout << " keyboard input :"
        //           << "now_time " << now_time << " key " << key << " scancode " << scancode << " action " << action << " mods " << mods << std::endl;
        m_key_list[key].NewAction(now_time, action);
    }

    // user query methods
    bool KeyInputSystem::KeyStateDown(int key)
    {
        return m_key_list[key].KeyStateDown();
    }

}