#ifndef MC_ASSET_BIN_BUFFER_H
#define MC_ASSET_BIN_BUFFER_H
#include <string>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

namespace mc::asset
{
    class AssetManager;
    class BinBuffer
    {
    public:
        BinBuffer(AssetManager &am, const std::string &file_path);
        ~BinBuffer();

    public:
        MD5SUM GetKey();

    private:
        const std::string m_file_path;
        std::string m_data;
        MD5SUM m_key;
    };
}
#endif
