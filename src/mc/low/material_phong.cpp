#include <vector>
//
#include <mc/engine.h>
#include <mc/material.h>
#include <mc/material_phong.h>
#include <mc/csv.h>

namespace mc::low
{
    // constructors
    MaterialPhong::MaterialPhong(const char *file_name) : m_file_name{file_name}
    {
        std::vector<float> data;
        mc::tools::CSVReader<float, int, int>::ReadMaterial(m_file_name, data);
        //
        m_ambient.x = data[0];
        m_ambient.y = data[1];
        m_ambient.z = data[2];
        //
        m_diffuse.x = data[3];
        m_diffuse.y = data[4];
        m_diffuse.z = data[5];
        //
        m_specular.x = data[6];
        m_specular.y = data[7];
        m_specular.z = data[8];
        //
        m_shininess = data[9] * 128.0f;
    }
    // virtual
    void MaterialPhong::SetShader(ShaderP shader)
    {
        m_shader = shader;
    }
    void MaterialPhong::PostUniform(Engine *eg, GameObject *gb)
    {
        m_shader->Use();
        m_texture->Use();
        // 传一些 uniform
        {
            m_shader->Uniform("ma_View", eg->GetCamera()->GetViewMat());
            m_shader->Uniform("ma_Proj", eg->GetCamera()->GetProjMat());
            m_shader->Uniform("lightPos", eg->GetLightPos());
            m_shader->Uniform("lightColor", eg->GetLightColor());
        }
        {
            m_shader->Uniform("material.ambient", m_ambient);
            m_shader->Uniform("material.diffuse", m_diffuse);
            m_shader->Uniform("material.specular", m_specular);
            m_shader->Uniform("material.shininess", m_shininess);
        }
        {
            m_shader->Uniform("ma_Model", gb->GetTransform()->GetWorldMat());
        }
    }
    void MaterialPhong::AddTexture(TextureP texture)
    {
        m_texture = texture;
    }
}