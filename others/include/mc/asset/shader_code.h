namespace mc::asset
{
    class ShaderCode;
}
#ifndef MC_ASSET_SHADER_CODE_H
#define MC_ASSET_SHADER_CODE_H

#include <string>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

namespace mc::asset
{
    class ShaderCode
    {
    public:
        ShaderCode(AssetManager &am, const std::string &r_name);
        ~ShaderCode();

    public:
        const char *GetData();

    public:
        MD5SUM GetKey();

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        std::string m_data; // vertex shader code
        MD5SUM m_key;
    };
}
#endif
