#include <mc/asset/asset_manager.h>

namespace mc::asset
{
    inline AssetManager::AssetManager() : m_art_factory{std::make_shared<ArtLogicFactory>()}
    {
    }
    inline ArtLogicFactory &AssetManager::GetAF()
    {
        return *m_art_factory;
    }
    inline const std::string &AssetManager::GetBaseDir()
    {
        return m_base_dir;
    }
    inline void AssetManager::SetBaseDir(const std::string &base_dir)
    {
        m_base_dir = base_dir;
    }

#define FUNCTION_SPECIAL
    template <>
    inline Store<Image> &AssetManager::getStore()
    {
        return m_image_store;
    }
    template <>
    inline Store<ShaderCode> &AssetManager::getStore()
    {
        return m_shader_code_store;
    }
    template <>
    inline Store<BinBuffer> &AssetManager::getStore()
    {
        return m_bin_buffer_store;
    }
    template <>
    inline Store<Texture> &AssetManager::getStore()
    {
        return m_texture_store;
    }
    template <>
    inline Store<Model> &AssetManager::getStore()
    {
        return m_model_store;
    }
    template <>
    inline Store<ShaderProgram> &AssetManager::getStore()
    {
        return m_shader_program_store;
    }
    template <>
    inline Store<Material> &AssetManager::getStore()
    {
        return m_material_store;
    }
    template <>
    inline Store<Node> &AssetManager::getStore()
    {
        return m_node_store;
    }
    template <>
    inline Store<Scene> &AssetManager::getStore()
    {
        return m_scene_store;
    }
    template <>
    inline Store<ArtLogic> &AssetManager::getStore()
    {
        return m_art_logic_store;
    }

#undef FUNCTION_SPECIAL

    template <typename T>
    inline void AssetManager::Reg(MD5SUM key, T *r_data)
    {
        auto &store{getStore<T>()};
        store.Register(key, r_data);
    }

    template <typename T>
    inline typename Store<T>::Elem AssetManager::Get(MD5SUM key)
    {
        auto &store{getStore<T>()};
        return store.Get(key);
    }

    template <typename T>
    inline void AssetManager::Del(MD5SUM key)
    {
        auto &store{getStore<T>()};
        store.Del(key);
    }

}