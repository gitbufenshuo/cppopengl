#include <string>
#include <iostream>

#include <image/stb_image.h>

#include <mc/asset/image.h>

namespace mc::asset
{

    Image::Image(const std::string &file_path) : m_file_path{file_path}
    {
        stbi_set_flip_vertically_on_load(true);

        m_image_data = stbi_load(file_path.data(), &m_width, &m_height, &m_nrChannels, 0);
        if (!m_image_data)
        {
            throw 1;
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

}
