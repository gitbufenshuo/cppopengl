#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <mc/asset/asset_manager.h>
#include <mc/asset/bin_buffer.h>
#include <mc/asset/md5sum.h>

#include <mc/tools/md5.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string BinBuffer::s_scope{"bin_buffer"};

    BinBuffer::BinBuffer(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                        m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        std::stringstream buffer;
        buffer << t.rdbuf();
        m_data = buffer.str();
        //
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<BinBuffer>(m_key, this);
        }
    }
    BinBuffer::~BinBuffer()
    {
        std::cout << "BinBuffer::~BinBuffer" << std::endl;
    }
    MD5SUM BinBuffer::GetKey()
    {
        return m_key;
    }
    const unsigned char *BinBuffer::GetData(int offset)
    {
        auto p{m_data.data()};
        p += offset;
        return reinterpret_cast<const unsigned char *>(p);
    }
}