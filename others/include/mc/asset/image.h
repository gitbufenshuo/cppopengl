#ifndef MC_ASSET_IMAGE_H
#define MC_ASSET_IMAGE_H

#include <string>
#include <string_view>

namespace mc::asset
{
    class Image
    {
    public:
        Image(const std::string &file_path);
        int GetWidth();
        int GetHeight();
        int GetNrChannels();

    private:
        const std::string m_file_path;
        int m_width;
        int m_height;
        int m_nrChannels;
        unsigned char *m_image_data;
    };
}
#endif