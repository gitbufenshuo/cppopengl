#ifndef GAME_LOGIC_CAMERA_LOGIC_H
#define GAME_LOGIC_CAMERA_LOGIC_H
#include <mc/logic_support.h>
#include <mc/transform.h>

namespace game
{

    class CamereLogic : public mc::low::LogicSupport
    {
        mc::low::Transform *m_ctl_transform;
        float m_now_yaw{0.0f};
        float m_now_pitch{0.0f};

    public:
        // constructors
        CamereLogic(mc::low::GameObject *gb, mc::low::Transform *ctl_t = nullptr);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif
