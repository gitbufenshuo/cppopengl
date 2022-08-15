#include <mc/texture.h>
#include <glad/glad.h>
#include <image/stb_image.h>

namespace mc::low
{
    Texture::Texture(const char *file_name) : m_file_name{file_name}
    {
        // read the file
    }
    void Texture::Load()
    {
    }
    void Texture::Use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }

}