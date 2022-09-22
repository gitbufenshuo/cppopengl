#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/art_logic/function_chart.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicFunctionChart::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicFunctionChart>()};
        return res;
    }
    void ArtLogicFunctionChart::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicFunctionChart::~ArtLogicFunctionChart()
    {
    }

    //
    void ArtLogicFunctionChart::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        // m_texture->Use();
        // 传一些 uniform
        {
            // for vertex shader (MVP 矩阵)
            m_sp->Uniform("uni_View", eg->GetCamera()->GetViewMat());
            m_sp->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
            m_sp->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
        }
    }
    void ArtLogicFunctionChart::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicFunctionChart::AddTexture(std::shared_ptr<mc::asset::Texture> texture)
    {
        m_texture = texture;
    }
    const std::string &ArtLogicFunctionChart::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }

}