#include <fstream>
#include <sstream>
#include <iostream>
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
    Texture::Texture(AssetManager &am, const std::string &file_path) : m_file_path{file_path}
    {
        std::ifstream t(file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", file_path);
            return;
        }
        MD5SUM image_key;
        mc::tools::MD5Sum(m_pb_data.image(), image_key.data);
        m_img = am.Get<Image>(image_key);
        if (!m_img)
        {
            SPD_WARN("Can't find Image ", m_pb_data.image());
        }
        load();
        mc::tools::MD5Sum(file_path, m_key.data);
    }

    Texture::~Texture()
    {
    }

    void Texture::load()
    {
        glGenTextures(1, &gl_id);
        glBindTexture(GL_TEXTURE_2D, gl_id);
        // copy the data to gpu
        int internal_format = m_img->GetNrChannels() == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_img->GetWidth(), m_img->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_img->GetData());
        glGenerateMipmap(GL_TEXTURE_2D);
        // settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_pb_data.wraps());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_pb_data.wrapt());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_pb_data.minfilter());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_pb_data.magfilter());
    }

} // namespace mc::asset
