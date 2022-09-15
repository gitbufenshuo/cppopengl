#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <mc/asset/asset_manager.h>
#include <mc/asset/shader_code.h>
#include <mc/asset/md5sum.h>

#include <mc/tools/md5.h>

namespace mc::asset
{

    using stdpath = std::filesystem::path;
    const std::string ShaderCode::s_scope{"shader_code"};

    ShaderCode::ShaderCode(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                          m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        std::stringstream buffer;
        buffer << t.rdbuf();
        m_data = buffer.str();
        //
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<ShaderCode>(m_key, this);
        }
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
