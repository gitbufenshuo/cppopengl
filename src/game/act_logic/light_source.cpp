#include <glm/glm.hpp>

#include <game/act_logic/light_source.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicLightSource::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicLightSource>()};
        res->m_gb = gb;
        return res;
    }
    ActLogicLightSource::~ActLogicLightSource() {}
    void ActLogicLightSource::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register(s_class_name, createFunc);
    }
    void ActLogicLightSource::Update(double delta_time)
    {
        move(delta_time);
        life(delta_time);
    }
    void ActLogicLightSource::move(double delta_time)
    {
        if (m_x > 20.0f)
        {
            m_x = -20.f;
        }
        // x move
        m_x += delta_time * 2.0f;
        // y and z
        auto y = glm::sin(m_time * 3.14f * 0.5f);
        auto z = glm::cos(m_time * 3.14f * 0.5f);
        m_gb->GetTransform()->SetLocalTranslate(m_x, y * 5.0f + 5.0f, z * 5.0f);
        // light pos
        m_gb->GetEngine()->SetLightPos(m_gb->GetTransform()->GetWorldPos());
        // light color
        m_gb->GetEngine()->SetLightColor(glm::vec3{0.5f * (y + 1.0f), 0.5f * (z + 1.0f), 1.0f});
    }
    void ActLogicLightSource::life(double delta_time)
    {
        m_time += delta_time;
    }
}