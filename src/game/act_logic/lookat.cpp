#include <iostream>
#include <memory>
#include <algorithm>

#include <mc/engine.h>
#include <game/act_logic/lookat.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicLookat::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicLookat>()};
        res->m_gb = gb;
    }

    void ActLogicLookat::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ActLogicLookat", createFunc);
    }
    ActLogicLookat::~ActLogicLookat() {}
    void ActLogicLookat::Update(double delta_time)
    {
        m_gb->GetTransform()->LookAt(m_ctl_transform);
    }
    void ActLogicLookat::BeforeRenderUpdate(double delta_time)
    {
    }
    void ActLogicLookat::AfterRenderUpdate(double delta_time)
    {
    }
}