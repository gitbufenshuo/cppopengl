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
        res->m_ctl_transform = gb->GetTransform();
        res->m_speed = 1.0f;
        return res;
    }

    void ActLogicRotate::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ActLogicRotate", createFunc);
    }
    ActLogicRotate::~ActLogicRotate() {}

    void ActLogicRotate::Update(double delta_time)
    {
        m_time += static_cast<float>(delta_time);
        if (mc::low::Engine::s_keyinput.KeyStateDown(80))
        {
            m_ctl_transform->Rotate(1.0f * m_speed, 0.0f, 0.0f, delta_time);
        }
    }

    void ActLogicRotate::BeforeRenderUpdate(double delta_time, unsigned int layer)
    {
    }
    void ActLogicRotate::AfterRenderUpdate(double delta_time, unsigned int layer)
    {
    }
}