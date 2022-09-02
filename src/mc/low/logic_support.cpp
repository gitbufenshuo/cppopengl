#include <glm/glm.hpp>

#include <mc/logic_support.h>

namespace mc::low
{
    // BasicLogicSupport
    BasicLogicSupport::BasicLogicSupport(GameObject *gb, float speed) : LogicSupport{gb}, m_speed{speed}
    {
        m_init_pos = gb->GetTransform()->GetWorldPos();
    }

    void BasicLogicSupport::Update(double delta_time)
    {
        float id = static_cast<float>(m_gb->GetID());
        float dt = static_cast<float>(delta_time);
        sum_time += dt;
        m_gb->GetTransform()->SetLocalEuler(sum_time * id * m_speed, sum_time * 65.0f, sum_time * 75.0f);
    }
    void BasicLogicSupport::RenderUpdate(double delta_time)
    {
    }

    // TranslateLogicSupport
    void TranslateLogicSupport::Update(double delta_time)
    {
        this->BasicLogicSupport::Update(delta_time); // 强制调用基类的虚函数
        m_gb->GetTransform()->SetLocalTranslate(
            glm::sin(sum_time) + m_init_pos.x,
            glm::sin(sum_time) + m_init_pos.y,
            glm::sin(sum_time) + m_init_pos.z);
    }
    // CameraLogicSupport
    CameraLogicSupport::CameraLogicSupport(GameObject *gb, float speed) : LogicSupport{gb}, m_speed{speed}
    {
        m_camera_transform = m_gb->GetEngine()->GetCamera()->GetTransform();
    }
    void CameraLogicSupport::Update(double delta_time)
    {
        float dt = static_cast<float>(delta_time);
        sum_time += dt;
        //
        auto gid = m_gb->GetID();
        if (gid == 1)
        {
            m_camera_transform->SetLocalTranslate(
                glm::sin(sum_time) * m_speed,
                glm::sin(sum_time) * m_speed,
                0.0f);
        }
    }
    void CameraLogicSupport::RenderUpdate(double delta_time)
    {
    }
}