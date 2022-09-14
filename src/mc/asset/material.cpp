#include <fstream>
#include <sstream>
#include <iostream>
// gl
#include <glad/glad.h>
// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/store.h>
#include <mc/asset/material.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{
    Material::Material(AssetManager &am, const std::string &file_path) : m_file_path{file_path}
    {
        std::ifstream t(file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", file_path);
            return;
        }
        MD5SUM _key;
        // Texture bind
        m_texture_list.resize(m_pb_data.texture_list_size());
        for (int tidx = 0; tidx < m_pb_data.texture_list_size(); ++tidx)
        {
            mc::tools::MD5Sum(m_pb_data.texture_list(tidx), _key.data);
            m_texture_list[tidx] = am.Get<Texture>(_key);
        }
        // ShaderProgram bind
        mc::tools::MD5Sum(m_pb_data.shader_program(), _key.data);
        m_program = am.Get<ShaderProgram>(_key);
        load();
        mc::tools::MD5Sum(file_path, m_key.data);
        am.Reg<Material>(m_key, this);
    }

    Material::~Material()
    {
    }

    void Material::load()
    {
    }
    MD5SUM Material::GetKey()
    {
        return m_key;
    }

} // namespace mc::asset
