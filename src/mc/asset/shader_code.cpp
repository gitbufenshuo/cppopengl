#include <fstream>
#include <sstream>
#include <iostream>

#include <mc/asset/shader_code.h>

namespace mc::asset
{
    ShaderCode::ShaderCode(const std::string &file_path) : m_file_path{file_path}
    {
        std::ifstream t(file_path.data());
        std::stringstream buffer;
        buffer << t.rdbuf();
        m_data = buffer.str();
    }
    ShaderCode::~ShaderCode()
    {
        std::cout << "ShaderCode::~ShaderCode" << std::endl;
    }
} // namespace mc::asset
