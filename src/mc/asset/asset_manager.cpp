#include <mc/asset/asset_manager.h>

namespace mc::asset
{
#define PRIVATE
    template <typename T>
    Store<T> AssetManager::getStore()
    {
        return aa;
    }
#undef PRIVATE

    template <typename T>
    void AssetManager::Reg(MD5SUM key, T *r_data)
    {
        auto store{getStore<T>()};
        store.Register(key, r_data);
    }
    // Store<Image>::Elem AssetManager::GetImage(MD5SUM key)
    // {
    //     return m_image_store.Get(key);
    // }

}