#include <mc/logic_support.h>

namespace mc::low
{
    void BasicLogicSupport::Update(double delta_time)
    {
        float id = static_cast<float>(m_gb->GetID());
        float dt = static_cast<float>(delta_time);
        sum_time += dt;
        m_gb->GetTransform()->SetLocalEuler(sum_time * id, sum_time * 65.0f, sum_time * 75.0f);
    }
}