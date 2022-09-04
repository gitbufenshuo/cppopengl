#ifndef GAME_LOGIC_CAMERA_LOGIC_H
#define GAME_LOGIC_CAMERA_LOGIC_H
#include <mc/logic_support.h>
#include <mc/transform.h>

namespace game
{

    class CamereLogic : public mc::low::LogicSupport
    {
        mc::low::Transform *m_camera_t;
        float m_now_yaw{0.0f};
        float m_now_pitch{0.0f};

    public:
        // constructors
        CamereLogic(mc::low::GameObject *gb);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif
