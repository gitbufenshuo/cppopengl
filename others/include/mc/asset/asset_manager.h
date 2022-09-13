#ifndef MC_ASSET_ASSET_MANAGER_H
#define MC_ASSET_ASSET_MANAGER_H

#include <mc/asset/store.h>
#include <mc/asset/image.h>
#include <mc/asset/shader_code.h>
#include <mc/asset/bin_buffer.h>
#include <mc/asset/texture.h>
#include <mc/asset/model.h>
#include <mc/asset/shader_program.h>
#include <mc/asset/material.h>

namespace mc::asset
{
    class BinBuffer;
    class ShaderCode;
    class Image;
    class Texture;
    class Model;
    class ShaderProgram;
    class Material;
    class AssetManager
    {
    public:
        template <typename T>
        inline void Reg(MD5SUM key, T *r_data);

        template <typename T>
        inline typename Store<T>::Elem Get(MD5SUM key);

        template <typename T>
        inline void Del(MD5SUM key);

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
    };
}
#include <mc/asset/asset_manager.inl>
#endif