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
#include <mc/asset/md5sum.h>

#include <mc/comm/pbmaterial.pb.h>

namespace mc::asset
{
    class Material
    {
    public:
        Material(AssetManager &am, const std::string &r_name);
        ~Material();

    public:
        void Use();
        MD5SUM GetKey();
        std::shared_ptr<ArtLogic> GetArtLogic();

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
    };
}
#endif
