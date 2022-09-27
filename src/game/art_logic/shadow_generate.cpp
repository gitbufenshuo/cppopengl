#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <game/art_logic/shadow_generate.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicShadowGenerate::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicShadowGenerate>()};
        return res;
    }
    void ArtLogicShadowGenerate::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicShadowGenerate::~ArtLogicShadowGenerate()
    {
    }

    //
    void ArtLogicShadowGenerate::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        // 传一些 uniform
        {
            // uni_lightSpaceMatrix
            // uni_model
            m_light->CalcLightMat();
            // for vertex shader (VP 矩阵)
            m_sp->Uniform("uni_lightSpaceMatrix", m_light->GetLightMat());
            m_sp->Uniform("uni_model", gb->GetTransform()->GetWorldMat());
        }
    }
    void ArtLogicShadowGenerate::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    const std::string &ArtLogicShadowGenerate::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }
    //
    void ArtLogicShadowGenerate::SetLight(std::shared_ptr<mc::asset::Light> _light)
    {
        m_light = _light;
    }

}