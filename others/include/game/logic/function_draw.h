#ifndef GAME_LOGIC_FUNCTION_DRAW_H
#define GAME_LOGIC_FUNCTION_DRAW_H

#include <mc/gameobject.h>
#include <mc/logic_support.h>

namespace game
{
    class FunctionDraw : public mc::low::LogicSupport
    {
    public:
        // constructors
        FunctionDraw(mc::low::GameObject *gb) : mc::low::LogicSupport{gb} {}

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}

#endif