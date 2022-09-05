#ifndef MC_LOW_KEYINPUTSYSTEM_H
#define MC_LOW_KEYINPUTSYSTEM_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace mc::low
{
    class KeyInputSystem
    {
    public:
        struct KeyAction
        {
            float time;
            int action;
        };
        class CircleKeyAction
        {
            std::vector<KeyAction> m_list;
            int m_index;

        public:
            CircleKeyAction();

        public:
            void NewAction(float time, int action);
            bool KeyStateDown();
        };

    public:
        // constructors
        KeyInputSystem();

    public:
        // overload operators
        void operator()(float, int, int, int, int);

    public:
        // user query methods
        bool KeyStateDown(int key); // 当前 key 是否是按下的状态

    private:
        std::vector<CircleKeyAction> m_key_list;
    };
}
#endif