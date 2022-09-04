#ifndef MC_LOW_KEYINPUTSYSTEM_H
#define MC_LOW_KEYINPUTSYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace mc::low
{
    class KeyInputSystem
    {
    public:
        // constructors
        KeyInputSystem() = default;

    public:
        // overload operators
        void operator()(int, int, int, int);

    public:
        // user query methods
        bool KeyStateDown(int key); // 当前 key 是否是按下的状态
    };
}
#endif