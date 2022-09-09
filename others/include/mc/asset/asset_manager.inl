#include <mc/asset/asset_manager.h>

namespace mc::asset
{
#define FUNCTION_SPECIAL
    template <>
    Store<Image> &AssetManager::getStore()
    {
        return m_image_store;
    }
    template <>
    Store<ShaderCode> &AssetManager::getStore()
    {
        return m_shader_code_store;
    }

#undef FUNCTION_SPECIAL

    template <typename T>
    void AssetManager::Reg(MD5SUM key, T *r_data)
    {
        auto &store{getStore<T>()};
        store.Register(key, r_data);
    }

    template <typename T>
    typename Store<T>::Elem AssetManager::Get(MD5SUM key)
    {
        auto &store{getStore<T>()};
        return store.Get(key);
    }

    template <typename T>
    void AssetManager::Del(MD5SUM key)
    {
        auto &store{getStore<T>()};
        store.Del(key);
    }

}