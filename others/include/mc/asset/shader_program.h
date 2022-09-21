namespace mc::asset
{
    class ShaderProgram;
}
#ifndef MC_ASSET_SHADER_PROGRAM_H
#define MC_ASSET_SHADER_PROGRAM_H

#include <string>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbshaderprogram.pb.h>

namespace mc::asset
{
    class ShaderProgram
    {
    public:
        ShaderProgram(AssetManager &am, const std::string &r_name);
        ShaderProgram(const std::string &v_code, const std::string &f_code);

        ~ShaderProgram();

    public:
        void Use();
        MD5SUM GetKey();
        void Uniform(const char *_name, const glm::mat4 &input);
        void Uniform(const char *_name, const glm::vec3 &input);
        void Uniform(const char *_name, const float input);

    private:
        void load(); // load to gl

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        mc::comm::PBShaderProgram m_pb_data;
        unsigned int gl_id{};
        MD5SUM m_key;
        std::shared_ptr<ShaderCode> m_vs{nullptr};
        std::shared_ptr<ShaderCode> m_fs{nullptr};
    };
}
#endif
