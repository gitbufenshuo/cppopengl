#include <algorithm>

#include <mc/engine.h>
#include <game/logic/camera_logic.h>

namespace game
{
    CamereLogic::CamereLogic(mc::low::GameObject *gb) : mc::low::LogicSupport{gb}
    {
        m_camera_t = gb->GetEngine()->GetCamera()->GetTransform();
    }

    void CamereLogic::Update(double delta_time)
    {
        float speed = 1.0f * static_cast<float>(delta_time);
        float xdiff = static_cast<float>(mc::low::Engine::s_c_xdiff);
        m_now_yaw -= xdiff * speed;
        float ydiff = static_cast<float>(mc::low::Engine::s_c_ydiff);
        m_now_pitch -= ydiff * speed;
        m_now_pitch = std::clamp(m_now_pitch, -89.0f, 89.0f);
        m_camera_t->SetLocalEuler(m_now_pitch, m_now_yaw, 0.0f);
    }

    void CamereLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void CamereLogic::AfterRenderUpdate(double delta_time)
    {
    }

}