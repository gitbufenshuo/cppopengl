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
        //
        // m_ctl_transform->ShowVersion();
        // return;
        // camera rotate
        float speed = 1.0f * static_cast<float>(delta_time);
        float xdiff = static_cast<float>(mc::low::Engine::s_c_xdiff);
        m_now_yaw -= xdiff * speed;
        float ydiff = static_cast<float>(mc::low::Engine::s_c_ydiff);
        m_now_pitch -= ydiff * speed;
        m_now_pitch = std::clamp(m_now_pitch, -89.0f, 89.0f);
        m_ctl_transform->SetLocalEuler(m_now_pitch, m_now_yaw, 0.0f);
        // camera translate
        speed *= 2.0f;
        if (mc::low::Engine::s_keyinput.KeyStateDown(65))
        {
            // A key
            m_ctl_transform->Move(glm::vec3{-speed, 0.0f, 0.0f});
            // m_ctl_transform->Move(glm::vec3{-speed, 0.0f, 0.0f}, mc::low::Space::World);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(68))
        {
            // D key
            m_ctl_transform->Move(glm::vec3{speed, 0.0f, 0.0f});
            // m_ctl_transform->Move(glm::vec3{speed, 0.0f, 0.0f}, mc::low::Space::World);
        }

        if (mc::low::Engine::s_keyinput.KeyStateDown(87))
        {
            // W key
            m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, -speed});
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, -speed}, mc::low::Space::World);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(83))
        {
            // S key
            m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, speed});
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, speed}, mc::low::Space::World);
        }
    }

    void CamereLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void CamereLogic::AfterRenderUpdate(double delta_time)
    {
    }
}