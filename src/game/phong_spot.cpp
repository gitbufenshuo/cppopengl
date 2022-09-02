#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>

#include <mc/csv.h>
#include <mc/material.h>

#include <game/phong_spot.h>

namespace game
{
    // constructors
    MaterialPhongSpot::MaterialPhongSpot(const char *file_name) : m_file_name{file_name}
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
    void MaterialPhongSpot::SetShader(ShaderP shader)
    {
        m_shader = shader;
    }
    void MaterialPhongSpot::PostUniform(Engine *eg, GameObject *gb)
    {
        m_shader->Use();
        m_texture->Use();
        // 传一些 uniform
        {
            // for vertex shader (MVP 矩阵)
            m_shader->Uniform("uni_View", eg->GetCamera()->GetViewMat());
            m_shader->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
            m_shader->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
            // for fragment shader (camera)
            m_shader->Uniform("uni_viewPos", eg->GetCamera()->GetTransform()->GetWorldPos());
            // for fragment shader (light)
            m_shader->Uniform("uni_spotLight.position", eg->GetCamera()->GetTransform()->GetWorldPos());
            m_shader->Uniform("uni_spotLight.direction", m_spot_light.direction);
            m_shader->Uniform("uni_spotLight.cutOff", m_spot_light.cutOff);
            m_shader->Uniform("uni_spotLight.outerCutOff", m_spot_light.outerCutOff);
            m_shader->Uniform("uni_spotLight.constant", m_spot_light.constant);
            m_shader->Uniform("uni_spotLight.linear", m_spot_light.linear);
            m_shader->Uniform("uni_spotLight.quadratic", m_spot_light.quadratic);
            m_shader->Uniform("uni_spotLight.ambient", m_spot_light.ambient);
            m_shader->Uniform("uni_spotLight.diffuse", m_spot_light.diffuse);
            m_shader->Uniform("uni_spotLight.specular", m_spot_light.specular);
            // for fragment shader (material)
            m_shader->Uniform("uni_material.specular", m_specular);
            m_shader->Uniform("uni_material.m_shininess", m_shininess);
        }
    }
    void MaterialPhongSpot::AddTexture(TextureP texture)
    {
        m_texture = texture;
    }
    void MaterialPhongSpot::ShowMe()
    {
        std::cout << "I am MaterialPhongSpot" << std::endl;
    }
    // static
    std::vector<mc::low::Material *> MaterialPhongSpot::LoadSurfaceDataFromFile(const char *filename)
    {
        std::vector<mc::low::Material *> temp_store;
        std::ifstream t(filename);
        //
        std::string row;
        std::string col;
        //
        int key = -1;
        std::string m_name;
        std::vector<float> _data_holder;
        _data_holder.reserve(10);
        //
        while (std::getline(t, row))
        {
            if (row.size() <= 1)
            {
                continue; // 空行
            }
            if (row[0] == '#')
            {
                if (key > -1)
                {
                    temp_store.push_back(new MaterialPhongSpot{
                        _data_holder,
                        m_name,
                    });
                }
                _data_holder.resize(0);
                ++key;
                std::stringstream row_stream{row};
                int loop = 0;
                while (std::getline(row_stream, col, '='))
                {
                    if (loop == 1)
                    {
                        m_name = col;
                        break;
                    }
                    // data.push_back(sto<T>(col));
                    loop++;
                }
                continue; // 注释行
            }
            std::stringstream row_stream{row};
            while (std::getline(row_stream, col, ','))
            {
                _data_holder.push_back(std::stof(col));
            }
        }
        return temp_store;
    }

}