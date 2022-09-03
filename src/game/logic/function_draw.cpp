#include <mc/engine.h>
#include <game/logic/function_draw.h>

namespace game
{
    void FunctionDraw::Update(double delta_time) {}
    void FunctionDraw::BeforeRenderUpdate(double delta_time)
    {
        mc::low::Engine::S_GL_EnableFaceCull(false);
    }
    void FunctionDraw::AfterRenderUpdate(double delta_time)
    {
        mc::low::Engine::S_GL_EnableFaceCull(true);
    }
}