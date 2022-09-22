#ifndef GAME_LOGIC_ROTATE_H
#define GAME_LOGIC_ROTATE_H

#include <mc/transform.h>
#include <mc/gameobject.h>

#include <mc/asset/act_logic.h>

namespace game
{

    class ActLogicRotate : public mc::asset::ActLogic
    {
        mc::low::Transform *m_ctl_transform;
        float m_time{0.0f};
        float m_speed{0.0f};
        //
    private:
        static std::shared_ptr<mc::asset::ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        ~ActLogicRotate() override;

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time, unsigned int layer) override;
        void AfterRenderUpdate(double delta_time, unsigned int layer) override;
    };
}
#endif
