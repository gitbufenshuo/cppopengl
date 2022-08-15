#include <iostream>
#include <string_view>
#include <fstream>
#include <sstream>
#include <algorithm>
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//
#include <mc/shader.h>

namespace mc::low
{
    char Shader::compileLog[512];
    Shader::Shader(const char *vname, const char *fname) : v_file_name{vname}, f_file_name{fname}
    {
    }
    void Shader::Load()
    {
        unsigned int vid = compile(GL_VERTEX_SHADER, v_file_name);
        unsigned int fid = compile(GL_FRAGMENT_SHADER, f_file_name);
        shader_id = glCreateProgram();
        glAttachShader(shader_id, vid);
        glAttachShader(shader_id, fid);
        glLinkProgram(shader_id);
        // check for linking errors
        int success;
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::fill(compileLog, compileLog + 512, 0);
            glGetProgramInfoLog(shader_id, 512, NULL, compileLog);
            std::cout << compileLog << std::endl;
            throw 1;
        }
        glDeleteShader(vid);
        glDeleteShader(fid);
    }
    void Shader::Use() const
    {
        glUseProgram(shader_id);
    }
    unsigned int Shader::compile(GLenum shader_type, const char *data)
    {
        unsigned int _shader = glCreateShader(shader_type);
        glShaderSource(_shader, 1, &data, NULL);
        glCompileShader(_shader);
        //
        int success;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::fill(compileLog, compileLog + 512, 0);
            glGetShaderInfoLog(_shader, 512, NULL, compileLog);
            std::cout << compileLog << std::endl;
            std::cout << data << std::endl;
            throw shader_type;
        }
        return _shader;
    }
    unsigned int Shader::compile(GLenum shader_type, std::string_view file_name)
    {

        std::ifstream t(file_name);
        std::stringstream buffer;
        buffer << t.rdbuf();
        auto s = buffer.str();
        const auto vdata = s.c_str();
        return compile(shader_type, vdata);
    }

}