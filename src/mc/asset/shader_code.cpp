#include <fstream>
#include <sstream>
#include <iostream>

#include <mc/asset/asset_manager.h>
#include <mc/asset/shader_code.h>
#include <mc/asset/md5sum.h>

#include <mc/tools/md5.h>

namespace mc::asset
{
    ShaderCode::ShaderCode(AssetManager &am, const std::string &file_path) : m_file_path{file_path}
    {
        std::ifstream t(file_path.data());
        std::stringstream buffer;
        buffer << t.rdbuf();
        m_data = buffer.str();
        //
        mc::tools::MD5Sum(file_path, m_key.data);
        //
        am.Reg<ShaderCode>(m_key, this);
    }
    ShaderCode::~ShaderCode()
    {
        std::cout << "ShaderCode::~ShaderCode" << std::endl;
    }
    MD5SUM ShaderCode::GetKey()
    {
        return m_key;
    }
    const char *ShaderCode::GetData()
    {
        return m_data.data();
    }
} // namespace mc::asset
