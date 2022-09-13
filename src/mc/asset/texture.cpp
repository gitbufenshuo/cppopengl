#include <fstream>
#include <sstream>
#include <iostream>

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
    Texture::Texture(const std::string &file_path)
    {
        std::ifstream t(file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", file_path);
            return;
        }
        MD5SUM temp;
        mc::tools::MD5Sum(m_pb_data.image(), temp.data);
    }

    Texture::~Texture()
    {
    }

    void Texture::link()
    {
    }

} // namespace mc::asset
