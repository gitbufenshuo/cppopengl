#include <glm/glm.hpp>

#include <mc/logic_support.h>

namespace mc::low
{
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
    void TranslateLogicSupport::Update(double delta_time)
    {
        float id = static_cast<float>(m_gb->GetID());
        this->BasicLogicSupport::Update(delta_time); // 强制调用基类的虚函数
        m_gb->GetTransform()->SetLocalTranslate(
            glm::sin(sum_time) + m_init_pos.x,
            glm::sin(sum_time) + m_init_pos.y,
            glm::sin(sum_time) + m_init_pos.z);
    }
}