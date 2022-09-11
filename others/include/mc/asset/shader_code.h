#ifndef MC_ASSET_SHADER_CODE_H
#define MC_ASSET_SHADER_CODE_H
#include <string>
namespace mc::asset
{
    class ShaderCode
    {
    public:
        ShaderCode(const std::string &file_path);
        ~ShaderCode();

    private:
        const std::string m_file_path;
        std::string m_data; // vertex shader code
    };
}
#endif
