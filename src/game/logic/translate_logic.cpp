#include <iostream>
#include <algorithm>

#include <mc/engine.h>
#include <game/logic/translate_logic.h>

namespace game
{
    TranslateLogic::TranslateLogic(mc::low::GameObject *gb) : mc::low::LogicSupport{gb}
    {
    }

    void TranslateLogic::Update(double delta_time)
    {
        m_time += static_cast<float>(delta_time);
        m_gb->GetTransform()->SetLocalTranslate(glm::sin(m_time * 1.28) * 5.0f, glm::cos(delta_time), glm::cos(m_time * 1.28) * 5.0f);
    }

    void TranslateLogic::BeforeRenderUpdate(double delta_time)
    {
    }
    void TranslateLogic::AfterRenderUpdate(double delta_time)
    {
    }
}