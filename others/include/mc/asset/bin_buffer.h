namespace mc::asset
{
    class BinBuffer;
}
#ifndef MC_ASSET_BIN_BUFFER_H
#define MC_ASSET_BIN_BUFFER_H
#include <string>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

namespace mc::asset
{
    class BinBuffer
    {
    public:
        BinBuffer(AssetManager &am, const std::string &r_name);
        ~BinBuffer();

    public:
        MD5SUM GetKey();
        const unsigned char *GetData(int offset);

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        std::string m_data;
        MD5SUM m_key;
    };
}
#endif
