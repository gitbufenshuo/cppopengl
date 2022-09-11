#include <iostream>
#include <algorithm>

#include <mc/engine.h>
#include <game/logic/rotate_logic.h>

namespace game
{
    RotateLogic::RotateLogic(mc::low::GameObject *gb) : mc::low::LogicSupport{gb}
    {
    }

    void RotateLogic::Update(double delta_time)
    {
        if (mc::low::Engine::s_keyinput.KeyStateDown(80))
        {
            m_speed = 50.0f;
            m_time += static_cast<float>(delta_time);
            m_gb->GetTransform()->SetLocalEuler(0.0f, m_time * m_speed, 0.0f);
        }
    }

    void RotateLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void RotateLogic::AfterRenderUpdate(double delta_time)
    {
    }
}