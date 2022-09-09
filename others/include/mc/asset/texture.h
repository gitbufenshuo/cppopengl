#ifndef MC_ASSET_TEXTURE_H
#define MC_ASSET_TEXTURE_H

#include <string>

#include <mc/comm/pbtexture.pb.h>

namespace mc::asset
{
    class Texture
    {
    public:
        Texture(const std::string &file_path);
        ~Texture();

    private:
        void link();

    private:
        const std::string m_file_path;
        mc::comm::PBTexture m_pb_data;
        unsigned int gl_id{};
    };
}
#endif
