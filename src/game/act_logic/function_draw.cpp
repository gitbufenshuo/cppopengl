#include <memory>

#include <mc/engine.h>
#include <mc/asset/act_logic.h>

#include <game/act_logic/function_draw.h>

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ArtLogicFunctionDraw::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicFunctionDraw>()};
        res->m_gb = gb;
        return res;
    }
    void ArtLogicFunctionDraw::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ArtLogicFunctionDraw", createFunc);
    }
    ArtLogicFunctionDraw::~ArtLogicFunctionDraw() {}
    void ArtLogicFunctionDraw::Update(double delta_time)
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
    void ArtLogicFunctionDraw::BeforeRenderUpdate(double delta_time, unsigned int layer)
    {
        mc::low::Engine::S_GL_EnableFaceCull(false);
    }
    void ArtLogicFunctionDraw::AfterRenderUpdate(double delta_time, unsigned int layer)
    {
        mc::low::Engine::S_GL_EnableFaceCull(true);
    }
}