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
            m_gb->GetTransform()->Rotate(1.0f, 0.0f, 0.0f, delta_time);
        }
    }

    void RotateLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void RotateLogic::AfterRenderUpdate(double delta_time)
    {
    }
}