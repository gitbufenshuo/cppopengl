#include <iostream>
#include <algorithm>

#include <mc/engine.h>
#include <game/logic/lookat_logic.h>

namespace game
{
    LookatLogic::LookatLogic(mc::low::GameObject *gb, mc::low::Transform *ctl_t) : mc::low::LogicSupport{gb}
    {
        m_ctl_transform = ctl_t;
    }

    void LookatLogic::Update(double delta_time)
    {
        m_gb->GetTransform()->LookAt(m_ctl_transform);
    }

    void LookatLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void LookatLogic::AfterRenderUpdate(double delta_time)
    {
    }
}