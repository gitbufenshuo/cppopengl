#ifndef MC_ASSET_BIN_BUFFER_H
#define MC_ASSET_BIN_BUFFER_H
#include <string>

namespace mc::asset
{
    class BinBuffer
    {
    public:
        BinBuffer(const std::string &file_path);
        ~BinBuffer();

    private:
        const std::string m_file_path;
        std::string m_data;
    };
}
#endif
