#include <iostream>
#include <algorithm>
#include <memory>

#include <mc/engine.h>
#include <game/act_logic/rotate.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicRotate::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicRotate>()};
        res->m_gb = gb;
    }

    void ActLogicRotate::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ActLogicRotate", createFunc);
    }
    ActLogicRotate::~ActLogicRotate() {}

    void ActLogicRotate::Update(double delta_time)
    {
        if (mc::low::Engine::s_keyinput.KeyStateDown(80))
        {
            m_gb->GetTransform()->Rotate(1.0f, 0.0f, 0.0f, delta_time);
        }
    }

    void ActLogicRotate::BeforeRenderUpdate(double delta_time)
    {
    }
    void ActLogicRotate::AfterRenderUpdate(double delta_time)
    {
    }
}