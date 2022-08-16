#include <iostream>

#ifndef MC_LOW_TEXTURE_H
#define MC_LOW_TEXTURE_H
namespace mc::low
{
    class Texture
    {
    public:
        Texture(const char *file_name);
        void Load();
        void Use();
        friend std::ostream &operator<<(std::ostream &, const Texture &self);

    private:
        const char *m_file_name;
        int m_width;
        int m_height;
        int m_nrChannels;
        unsigned char *m_image_data{nullptr};
        //
        unsigned int m_texture_id{};
    };
}
#endif