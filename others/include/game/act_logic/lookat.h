#ifndef GAME_LOGIC_LOOKAT_H
#define GAME_LOGIC_LOOKAT_H

#include <mc/transform.h>

#include <mc/gameobject.h>

#include <mc/asset/act_logic.h>

namespace game
{

    class ActLogicLookat : public mc::asset::ActLogic
    {
        mc::low::Transform *m_ctl_transform;
        float m_time{0.0f};

    private:
        static std::shared_ptr<mc::asset::ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        ~ActLogicLookat() override;

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif
