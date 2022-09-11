#include <fstream>
#include <sstream>
#include <iostream>

#include <mc/asset/texture.h>

#include <mc/log/log.h>

namespace mc::asset
{

    Texture::Texture(const std::string &file_path)
    {
        std::ifstream t(file_path.data());
        if (m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", file_path);
        }
    }

    Texture::~Texture()
    {
    }

    void Texture::link()
    {
    }

} // namespace mc::asset
