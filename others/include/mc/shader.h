#ifndef SHADER_H
#define SHADER_H

#include <string_view>
//
#include <glad/glad.h>

namespace mc::low
{
    class Shader
    {
    public:
        using PROGRAM_t = unsigned int;
        Shader(const char *vname, const char *fname);
        void Load();
        void Use() const;

    private:
        std::string_view v_file_name;
        std::string_view f_file_name;
        PROGRAM_t shader_id;
        static char compileLog[512];

    private:
        unsigned int compile(GLenum shader_type, const char *data);
        unsigned int compile(GLenum shader_type, std::string_view file_name);
    };
}

#endif