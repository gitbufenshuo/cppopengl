#ifndef GAME_ACT_LOGIC_LIGHT_SOURCE_H
#define GAME_ACT_LOGIC_LIGHT_SOURCE_H

#include <string>

#include <glm/glm.hpp>

#include <mc/engine.h>
#include <mc/gameobject.h>
#include <mc/transform.h>

#include <mc/asset/act_logic.h>
#include <mc/asset/art_logic.h>

namespace game
{
    class ActLogicLightSource : public mc::asset::ActLogic
    {
    public:
        inline static const std::string s_class_name{"game::act_logic::ActLogicLightSource"};

    private:
        static std::shared_ptr<ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        ~ActLogicLightSource() override;

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        void Update(double delta_time) override;

    private:
        void move(double delta_time);
        void life(double delta_time);

    private:
        float m_time{0.0f};
        float m_x{-20.0f};
    };
}

#endif