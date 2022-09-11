#ifndef GAME_LOGIC_TRANSLATE_LOGIC_H
#define GAME_LOGIC_TRANSLATE_LOGIC_H
#include <mc/logic_support.h>
#include <mc/transform.h>

namespace game
{

    class TranslateLogic : public mc::low::LogicSupport
    {
        float m_time{0.0f};
        float m_speed{0.0f};

    public:
        // constructors
        TranslateLogic(mc::low::GameObject *gb);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif
