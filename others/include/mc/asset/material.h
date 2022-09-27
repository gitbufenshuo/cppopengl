namespace mc::asset
{
    class Material;
}

#ifndef MC_ASSET_MATERIAL_H
#define MC_ASSET_MATERIAL_H

#include <string>
#include <vector>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/art_logic.h>
#include <mc/asset/texture.h>
#include <mc/asset/shader_program.h>

#include <mc/asset/md5sum.h>

#include <mc/comm/pbmaterial.pb.h>

namespace mc::asset
{
    inline constexpr unsigned int RENDER_LAYER_OUTLINE = 0x01; // 画轮廓
    class Material
    {
    public:
        Material(AssetManager &am, const std::string &r_name);
        Material(const Material &other);
        ~Material();

    public:
        void Use();
        MD5SUM GetKey();
        std::shared_ptr<ArtLogic> GetArtLogic();
        void SetRenderBit(unsigned int bit, bool set);
        bool GetRenderBit(unsigned int bit);
        bool GetCastShadow() const;
        bool GetRecShadow() const;
        void SetCastShadow(bool);
        void SetRecShadow(bool);

    private:
        void load(); // load to gl

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        mc::comm::PBMaterial m_pb_data;
        MD5SUM m_key;
        std::vector<std::shared_ptr<Texture>> m_texture_list;
        std::shared_ptr<ShaderProgram> m_program;
        std::shared_ptr<ArtLogic> m_art_logic;
        unsigned int m_render_bit{0};
        bool m_cast_shadow{false}; // 产生阴影
        bool m_rec_shadow{false};  // 接收阴影
    };
}
#endif
