
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>

#include <mc/csv.h>
#include <mc/material.h>
#include <game/blinn_phong_point.h>

namespace game
{
    // constructors
    MaterialBlinnPhongPoint::MaterialBlinnPhongPoint(const char *file_name) : m_file_name{file_name}
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
        m_shininess = data[9] * 360.0f;
    }
    // virtual
    void MaterialBlinnPhongPoint::SetShader(ShaderP shader)
    {
        m_shader = shader;
    }
    void MaterialBlinnPhongPoint::PostUniform(Engine *eg, GameObject *gb)
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
    void MaterialBlinnPhongPoint::AddTexture(TextureP texture)
    {
        m_texture = texture;
    }
    std::vector<mc::low::Material *> MaterialBlinnPhongPoint::LoadSurfaceDataFromFile(const char *filename)
    {
        std::vector<Material *> temp_store;
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
                    temp_store.push_back(new MaterialBlinnPhongPoint{
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