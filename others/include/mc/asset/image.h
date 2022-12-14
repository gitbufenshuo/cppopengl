namespace mc::asset
{
    class Image;
}
#ifndef MC_ASSET_IMAGE_H
#define MC_ASSET_IMAGE_H

#include <string>
#include <string_view>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

namespace mc::asset
{
    class Image
    {
    public:
        Image(AssetManager &am, const std::string &r_name);
        ~Image();

    public:
        int GetWidth();
        int GetHeight();
        int GetNrChannels();
        MD5SUM GetKey();
        unsigned char *GetData();

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // image
        int m_width;
        int m_height;
        int m_nrChannels;
        MD5SUM m_key;
        unsigned char *m_image_data;
    };
}
#endif