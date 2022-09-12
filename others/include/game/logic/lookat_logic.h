#ifndef GAME_LOGIC_LOOKAT_LOGIC_H
#define GAME_LOGIC_LOOKAT_LOGIC_H
#include <mc/logic_support.h>
#include <mc/transform.h>

namespace game
{

    class LookatLogic : public mc::low::LogicSupport
    {
        mc::low::Transform *m_ctl_transform;
        float m_time{0.0f};

    public:
        // constructors
        LookatLogic(mc::low::GameObject *gb, mc::low::Transform *ctl_t);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif
