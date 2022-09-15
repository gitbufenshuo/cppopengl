namespace mc::asset
{
    class AssetManager;
}

#ifndef MC_ASSET_ASSET_MANAGER_H
#define MC_ASSET_ASSET_MANAGER_H

#include <memory>
#include <string>

// asset
#include <mc/asset/store.h>
#include <mc/asset/image.h>
#include <mc/asset/shader_code.h>
#include <mc/asset/bin_buffer.h>
#include <mc/asset/texture.h>
#include <mc/asset/model.h>
#include <mc/asset/shader_program.h>
#include <mc/asset/material.h>
#include <mc/asset/node.h>
#include <mc/asset/scene.h>
#include <mc/asset/art_logic.h>

namespace mc::asset
{
    class AssetManager
    {
    public:
        inline AssetManager();
        inline const std::string &GetBaseDir();

    public:
        template <typename T>
        inline void Reg(MD5SUM key, T *r_data);

        template <typename T>
        inline typename Store<T>::Elem Get(MD5SUM key);

        template <typename T>
        inline void Del(MD5SUM key);

    public:
        inline ArtLogicFactory &GetAF();

    private:
        template <typename T>
        inline Store<T> &getStore();

    private:
        Store<Image> m_image_store;
        Store<ShaderCode> m_shader_code_store;
        Store<BinBuffer> m_bin_buffer_store;
        Store<Texture> m_texture_store;
        Store<Model> m_model_store;
        Store<ShaderProgram> m_shader_program_store;
        Store<Material> m_material_store;
        Store<Node> m_node_store;
        Store<Scene> m_scene_store;
        Store<ArtLogic> m_art_logic_store;
        std::shared_ptr<ArtLogicFactory> m_art_factory;
        std::string m_base_dir;
    };
}
#include <mc/asset/asset_manager.inl>
#endif