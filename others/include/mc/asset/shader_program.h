#ifndef MC_ASSET_SHADER_PROGRAM_H
#define MC_ASSET_SHADER_PROGRAM_H

#include <string>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbshaderprogram.pb.h>

namespace mc::asset
{
    class AssetManager;

    class ShaderProgram
    {
    public:
        ShaderProgram(AssetManager &am, const std::string &file_path);
        ~ShaderProgram();

    public:
        void Use();
        MD5SUM GetKey();

    private:
        void load(); // load to gl

    private:
        const std::string m_file_path;
        mc::comm::PBShaderProgram m_pb_data;
        unsigned int gl_id{};
        MD5SUM m_key;
        std::shared_ptr<ShaderCode> m_vs{nullptr};
        std::shared_ptr<ShaderCode> m_fs{nullptr};
    };
}
#endif
