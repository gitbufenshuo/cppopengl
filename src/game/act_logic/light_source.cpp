#include <glm/glm.hpp>

#include <game/act_logic/light_source.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicLightSource::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicLightSource>()};
        res->m_gb = gb;
        res->m_light_index = bin_data[0] - '0';
        if (res->m_light_index == 0)
        {
            res->m_x = 3.14f / 3.0f;
        }
        else if (res->m_light_index == 1)
        {
            res->m_x = 3.14f;
        }
        else
        {
            res->m_x = 6.28f / 3.0f;
        }
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
        // x and y and z
        auto x = glm::sin(m_time * 3.14f * 2.0f * 0.1f + m_x) * 20.0f;
        auto y = glm::sin(m_time * 3.14f * 0.5f);
        auto z = glm::cos(m_time * 3.14f * 0.5f);
        m_gb->GetTransform()->SetLocalTranslate(x, y * 5.0f + 5.0f, z * 5.0f);
        m_gb->GetTransform()->LookAt(glm::vec3{0.0f, 0.0f, 0.0f});
        //  light pos
        auto _light{m_gb->GetEngine()->GetLight(m_light_index)};
        _light->SetPos(m_gb->GetTransform()->GetWorldPos());
        _light->SetColor(glm::vec3{1.0f, 1.0f, 1.0f});
        // _light->SetForward(m_gb->GetTransform()->GetWorldZ() - m_gb->GetTransform()->GetWorldPos());
    }
    void ActLogicLightSource::life(double delta_time)
    {
        m_time += delta_time;
    }
}