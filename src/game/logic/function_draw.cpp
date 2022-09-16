#include <mc/engine.h>
#include <game/logic/function_draw.h>

namespace game
{
    void FunctionDraw::Update(double delta_time)
    {
        static float s_time{0.0f};
        s_time += static_cast<float>(delta_time);
        if (s_time > 1.0f)
        {
            s_time = 0.0f;
        }
        // 每一帧，换 model 里面的 m_v_data1
        auto model(m_gb->GetMeshFilter()->GetModel(0));
    }
    void FunctionDraw::BeforeRenderUpdate(double delta_time)
    {
        mc::low::Engine::S_GL_EnableFaceCull(false);
    }
    void FunctionDraw::AfterRenderUpdate(double delta_time)
    {
        mc::low::Engine::S_GL_EnableFaceCull(true);
    }
}