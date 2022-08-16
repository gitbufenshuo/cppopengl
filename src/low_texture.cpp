#include <iostream>
//
#include <mc/texture.h>
#include <glad/glad.h>
#include <image/stb_image.h>

namespace mc::low
{
    Texture::Texture(const char *file_name) : m_file_name{file_name}
    {
        m_image_data = stbi_load(file_name, &m_width, &m_height, &m_nrChannels, 0);
        std::cout << m_width << " " << m_height << " " << m_nrChannels << std::endl;
        if (!m_image_data)
        {
            throw 1;
        }
    }
    void Texture::Load()
    {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        // copy the data to gpu
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // free the image data in memory
        stbi_image_free(m_image_data);
    }
    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }
    // friends
    std::ostream &operator<<(std::ostream &cout, const Texture &self)
    {
        std::cout << "Texture:" << self.m_file_name << std::endl;
        return cout;
    }

}