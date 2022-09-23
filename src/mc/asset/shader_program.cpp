#include <fstream>
#include <sstream>
#include <iostream>
// gl
#include <glad/glad.h>
// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/store.h>
#include <mc/asset/shader_program.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace
{
    unsigned int compile(GLenum shader_type, const char *data, char *compileLog)
    {
        unsigned int _shader = glCreateShader(shader_type);
        glShaderSource(_shader, 1, &data, nullptr);
        glCompileShader(_shader);
        //
        int success;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::fill(compileLog, compileLog + 512, 0);
            glGetShaderInfoLog(_shader, 512, nullptr, compileLog);
            std::cout << compileLog << std::endl;
            std::cout << data << std::endl;
            throw shader_type;
        }
        return _shader;
    }
}

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string ShaderProgram::s_scope{"shader_program"};

    ShaderProgram::ShaderProgram(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Texuture()", m_file_path);
            return;
        }
        MD5SUM shader_code_key;
        mc::tools::MD5Sum(m_pb_data.vs(), shader_code_key.data);
        m_vs = am.Get<ShaderCode>(shader_code_key);
        if (!m_vs)
        {
            SPD_WARN("Can't find ShaderCode VS ", m_pb_data.vs());
        }
        mc::tools::MD5Sum(m_pb_data.fs(), shader_code_key.data);
        m_fs = am.Get<ShaderCode>(shader_code_key);
        if (!m_fs)
        {
            SPD_WARN("Can't find ShaderCode FS", m_pb_data.fs());
        }
        load();
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<ShaderProgram>(m_key, this);
        }
    }

    ShaderProgram::ShaderProgram(const std::string &v_code, const std::string &f_code)
    {
        char compileLog[512];
        unsigned int vid = compile(GL_VERTEX_SHADER, v_code.data(), compileLog);
        unsigned int fid = compile(GL_FRAGMENT_SHADER, f_code.data(), compileLog);
        gl_id = glCreateProgram();
        glAttachShader(gl_id, vid);
        glAttachShader(gl_id, fid);
        glLinkProgram(gl_id);
        // check for linking errors
        int success;
        glGetProgramiv(gl_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::fill(compileLog, compileLog + 512, 0);
            glGetProgramInfoLog(gl_id, 512, nullptr, compileLog);
            std::cout << compileLog << std::endl;
            throw 1;
        }
        glDeleteShader(vid);
        glDeleteShader(fid);
    }

    ShaderProgram::~ShaderProgram()
    {
    }

    void ShaderProgram::load()
    {
        char compileLog[512];
        unsigned int vid = compile(GL_VERTEX_SHADER, m_vs->GetData(), compileLog);
        unsigned int fid = compile(GL_FRAGMENT_SHADER, m_fs->GetData(), compileLog);
        gl_id = glCreateProgram();
        glAttachShader(gl_id, vid);
        glAttachShader(gl_id, fid);
        glLinkProgram(gl_id);
        // check for linking errors
        int success;
        glGetProgramiv(gl_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::fill(compileLog, compileLog + 512, 0);
            glGetProgramInfoLog(gl_id, 512, nullptr, compileLog);
            std::cout << compileLog << std::endl;
            throw 1;
        }
        glDeleteShader(vid);
        glDeleteShader(fid);
    }
    void ShaderProgram::Use()
    {
        glUseProgram(gl_id);
    }
    MD5SUM ShaderProgram::GetKey()
    {
        return m_key;
    }
    void ShaderProgram::Uniform(const char *_name, const glm::mat3 &input)
    {
        glUniformMatrix3fv(glGetUniformLocation(gl_id, _name), 1, GL_FALSE, &input[0][0]);
    }
    void ShaderProgram::Uniform(const char *_name, const glm::mat4 &input)
    {
        glUniformMatrix4fv(glGetUniformLocation(gl_id, _name), 1, GL_FALSE, &input[0][0]);
    }
    void ShaderProgram::Uniform(const char *_name, const glm::vec3 &input)
    {
        glUniform3fv(glGetUniformLocation(gl_id, _name), 1, &input[0]);
    }
    void ShaderProgram::Uniform(const char *_name, const float input)
    {
        glUniform1f(glGetUniformLocation(gl_id, _name), input);
    }
    void ShaderProgram::Uniform(const char *_name, const int input)
    {
        glUniform1i(glGetUniformLocation(gl_id, _name), input);
    }

} // namespace mc::asset
