#ifndef GAME_ACT_LOGIC_GBCD_H
#define GAME_ACT_LOGIC_GBCD_H

#include <glm/glm.hpp>

#include <mc/engine.h>
#include <mc/gameobject.h>
#include <mc/transform.h>

#include <mc/asset/act_logic.h>

namespace game
{
    class ActLogicGBCD : public mc::asset::ActLogic
    {
    private:
        static std::shared_ptr<ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        ~ActLogicGBCD() override;

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;

    private:
        void move(double delta_time);
        void life(double delta_time);

    private:
        mc::low::Transform *m_tr;
        mc::low::Engine *m_eg;
        float m_time{0.0f};
        glm::vec3 m_outdir{0.05f, 0.05f, 0.05f};
        int moving_state{};
    };
}

#endif