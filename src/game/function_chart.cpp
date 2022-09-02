#include <mc/material.h>
#include <game/function_chart.h>

namespace game
{
    // constructors
    MaterialFunctionChart::MaterialFunctionChart() {}
    // virtual
    void MaterialFunctionChart::SetShader(ShaderP shader)
    {
        m_shader = shader;
    }
    void MaterialFunctionChart::PostUniform(Engine *eg, GameObject *gb)
    {
        m_shader->Use();
        // m_texture->Use();
        // 传一些 uniform
        {
            // for vertex shader (MVP 矩阵)
            m_shader->Uniform("uni_View", eg->GetCamera()->GetViewMat());
            m_shader->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
            m_shader->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
        }
    }
    void MaterialFunctionChart::AddTexture(TextureP texture)
    {
        m_texture = texture;
    }
    void MaterialFunctionChart::ShowMe()
    {
        std::cout << "I am MaterialFunctionChart" << std::endl;
    }
}