#include <iostream>
#include <algorithm>

#include <mc/engine.h>
#include <game/logic/camera_logic.h>

namespace game
{
    CamereLogic::CamereLogic(mc::low::GameObject *gb, mc::low::Transform *ctl_t) : mc::low::LogicSupport{gb}
    {
        if (!ctl_t)
        {
            m_ctl_transform = gb->GetEngine()->GetCamera()->GetTransform();
        }
        else
        {
            m_ctl_transform = ctl_t;
        }
    }

    void CamereLogic::Update(double delta_time)
    {
        // camera rotate
        float speed = 1.0f * static_cast<float>(delta_time);
        float xdiff = static_cast<float>(mc::low::Engine::s_c_xdiff);
        m_now_yaw -= xdiff * speed;
        float ydiff = static_cast<float>(mc::low::Engine::s_c_ydiff);
        m_now_pitch -= ydiff * speed;
        m_now_pitch = std::clamp(m_now_pitch, -89.0f, 89.0f);
        m_ctl_transform->SetLocalEuler(m_now_pitch, m_now_yaw, 0.0f);
        // camera translate
        glm::vec3 t_x = m_ctl_transform->GetWorldX();
        glm::vec3 t_z = m_ctl_transform->GetWorldZ();
        glm::vec3 t_o = m_ctl_transform->GetWorldPos();
        glm::vec3 t_d = t_o - t_z;
        glm::vec3 t_r = t_x - t_o;
        glm::vec3 t_l = -t_r;
        //
        speed *= 2.0f;
        if (mc::low::Engine::s_keyinput.KeyStateDown(65))
        {
            // A key
            m_ctl_transform->IncLocalTranslate(t_l.x * speed, t_l.y * speed, t_l.z * speed);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(68))
        {
            // W key
            m_ctl_transform->IncLocalTranslate(t_r.x * speed, t_r.y * speed, t_r.z * speed);
        }

        if (mc::low::Engine::s_keyinput.KeyStateDown(87))
        {
            // W key
            m_ctl_transform->IncLocalTranslate(t_d.x * speed, 0.0f, t_d.z * speed);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(83))
        {
            // S key
            m_ctl_transform->IncLocalTranslate(-t_d.x * speed, 0.0f, -t_d.z * speed);
        }
    }

    void CamereLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void CamereLogic::AfterRenderUpdate(double delta_time)
    {
    }
}