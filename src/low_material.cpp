#include <vector>
//
#include <mc/material.h>
#include <mc/csv.h>

namespace mc::low
{
    Material::Material(const char *file_name) : m_file_name{file_name}
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
}