#include <iostream>
#include <algorithm>
#include <memory>

#include <mc/engine.h>
#include <game/act_logic/translate.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicTranslate::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicTranslate>()};
        res->m_gb = gb;
    }

    void ActLogicTranslate::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ActLogicTranslate", createFunc);
    }
    ActLogicTranslate::~ActLogicTranslate() {}

    void ActLogicTranslate::Update(double delta_time)
    {
        m_time += static_cast<float>(delta_time);
        m_gb->GetTransform()->SetLocalTranslate(glm::sin(m_time * 1.28) * 5.0f, glm::cos(delta_time), glm::cos(m_time * 1.28) * 5.0f);
    }
    void ActLogicTranslate::BeforeRenderUpdate(double delta_time)
    {
    }
    void ActLogicTranslate::AfterRenderUpdate(double delta_time)
    {
    }
}