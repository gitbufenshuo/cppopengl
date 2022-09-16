namespace mc::asset
{
    class Texture;
}

#ifndef MC_ASSET_TEXTURE_H
#define MC_ASSET_TEXTURE_H

#include <string>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbtexture.pb.h>

namespace mc::asset
{
    class Texture
    {
    public:
        Texture(AssetManager &am, const std::string &r_name);
        ~Texture();

    public:
        void Use();

    private:
        void load(); // load to gl

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        mc::comm::PBTexture m_pb_data;
        unsigned int gl_id{};
        MD5SUM m_key;
        std::shared_ptr<Image> m_img{nullptr};
    };
}
#endif
