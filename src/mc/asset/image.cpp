#include <string>
#include <iostream>
#include <filesystem>

#include <image/stb_image.h>

#include <mc/asset/asset_manager.h>
#include <mc/asset/image.h>
#include <mc/asset/md5sum.h>

#include <mc/tools/md5.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Image::s_scope{"image"};

    Image::Image(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {
        stbi_set_flip_vertically_on_load(false);

        m_image_data = stbi_load(m_file_path.data(), &m_width, &m_height, &m_nrChannels, 0);
        if (!m_image_data)
        {
            throw 1;
        }
        //
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Image>(m_key, this);
        }
    }
    Image::~Image()
    {
        stbi_image_free(m_image_data);
        std::cout << " Image Clear" << std::endl;
    }

    int Image::GetWidth() { return m_width; }
    int Image::GetHeight() { return m_height; }
    int Image::GetNrChannels() { return m_nrChannels; }
    MD5SUM Image::GetKey() { return m_key; }
    unsigned char *Image::GetData() { return m_image_data; }

}
