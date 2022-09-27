#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

// gl
#include <glad/glad.h>
// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/store.h>
#include <mc/asset/texture.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Texture::s_scope{"texture"};

    Texture::Texture(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                    m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", m_file_path);
            return;
        }
        load(am);
        mc::tools::MD5Sum(r_name, m_key.data);
        am.Reg<Texture>(m_key, this);
    }

    Texture::~Texture()
    {
        SPD_INFO("Texture::~Texture() addr:{}", static_cast<void *>(this));
    }
    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(m_pb_data.texture_type(), gl_id);
    }
    void Texture::load_cubemap(AssetManager &am)
    {
        //
        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, gl_id);
        // 加载六张图
        MD5SUM image_key;
        int internal_format{};
        for (int index = 0; index < 6; ++index)
        {
            mc::tools::MD5Sum(m_pb_data.image_list(index), image_key.data);
            SPD_INFO("Texture::load_cubemap {}", m_pb_data.image_list(index));
            auto one_image{am.Get<Image>(image_key)};
            internal_format = one_image->GetNrChannels() == 3 ? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
                         0, internal_format, one_image->GetWidth(), one_image->GetHeight(), 0, internal_format, GL_UNSIGNED_BYTE, one_image->GetData());
        }
        //
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_pb_data.minfilter());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_pb_data.magfilter());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_pb_data.wraps());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_pb_data.wrapt());
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, m_pb_data.wrapr());
    }
    void Texture::load_texture_2d(AssetManager &am)
    {
        MD5SUM image_key;
        mc::tools::MD5Sum(m_pb_data.image(), image_key.data);
        SPD_INFO("Texture::load_texture_2d {}", m_pb_data.image());
        auto _img{am.Get<Image>(image_key)};
        //
        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_2D, gl_id);
        // copy the data to gpu
        int internal_format = _img->GetNrChannels() == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _img->GetWidth(), _img->GetHeight(), 0, internal_format, GL_UNSIGNED_BYTE, _img->GetData());
        glGenerateMipmap(GL_TEXTURE_2D);
        // settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_pb_data.minfilter());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_pb_data.magfilter());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_pb_data.wraps());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_pb_data.wrapt());
    }
    void Texture::load(AssetManager &am)
    {
        if (m_pb_data.texture_type() == 0)
        {
            m_pb_data.set_texture_type(GL_TEXTURE_2D);
        }
        switch (m_pb_data.texture_type())
        {
        case GL_TEXTURE_2D:
            load_texture_2d(am);
            break;
        case GL_TEXTURE_CUBE_MAP:
            load_cubemap(am);
        default:
            break;
        }
    }

} // namespace mc::asset
