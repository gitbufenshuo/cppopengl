#ifndef MC_ASSET_IMAGE_H
#define MC_ASSET_IMAGE_H

#include <string>
#include <string_view>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

namespace mc::asset
{
    class AssetManager;
    class Image
    {
    public:
        Image(AssetManager &am, const std::string &file_path);
        ~Image();

    public:
        int GetWidth();
        int GetHeight();
        int GetNrChannels();
        MD5SUM GetKey();
        unsigned char *GetData();

    private:
        const std::string m_file_path;
        int m_width;
        int m_height;
        int m_nrChannels;
        MD5SUM m_key;
        unsigned char *m_image_data;
    };
}
#endif