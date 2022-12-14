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
    using stdpath = std::filesystem::path;
    const std::string Material::s_scope{"material"};

    Material::Material(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                      m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", m_file_path);
            return;
        }
        MD5SUM _key;
        {
            // Texture bind
            m_texture_list.resize(m_pb_data.texture_list_size());
            for (int tidx = 0; tidx < m_pb_data.texture_list_size(); ++tidx)
            {
                mc::tools::MD5Sum(m_pb_data.texture_list(tidx), _key.data);
                m_texture_list[tidx] = am.Get<Texture>(_key);
            }
        }
        {
            // ShaderProgram bind
            mc::tools::MD5Sum(m_pb_data.shader_program(), _key.data);
            m_program = am.Get<ShaderProgram>(_key);
        }
        {
            // ArtLogic create
            auto &arf{am.GetARF()};
            mc::tools::MD5Sum(m_pb_data.art_logic(), _key.data);
            auto al{am.Get<ArtLogic>(_key)};
            m_art_logic = arf.Create(al->GetLogicName(), al->GetBinData());
            // set ArtLogic Texture
            for (auto one : m_texture_list)
            {
                m_art_logic->AddTexture(one);
            }
            // set ArtLogic Program
            m_art_logic->SetShaderProgram(m_program);
        }
        load();
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Material>(m_key, this);
        }
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
    std::shared_ptr<ArtLogic> Material::GetArtLogic()
    {
        return m_art_logic;
    }
    Material::Material(const Material &other) : m_art_logic{other.m_art_logic->Clone()}
    {
    }
    void Material::SetRenderBit(unsigned int bit, bool set)
    {
        if (!set)
        {
            m_render_bit |= (~bit);
        }
        else
        {
            m_render_bit |= (bit);
        }
    }
    bool Material::GetRenderBit(unsigned int bit)
    {
        return m_render_bit & bit;
    }
    bool Material::GetCastShadow() const
    {
        return m_cast_shadow;
    }
    bool Material::GetRecShadow() const
    {
        return m_rec_shadow;
    }
    void Material::SetCastShadow(bool v)
    {
        m_cast_shadow = v;
    }
    void Material::SetRecShadow(bool v)
    {
        m_rec_shadow = v;
    }

} // namespace mc::asset
