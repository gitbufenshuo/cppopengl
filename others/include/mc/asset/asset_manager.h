#ifndef MC_ASSET_ASSET_MANAGER_H
#define MC_ASSET_ASSET_MANAGER_H

#include <mc/asset/store.h>
#include <mc/asset/image.h>

namespace mc::asset
{
    class AssetManager
    {
    public:
        template <typename T>
        void Reg(MD5SUM key, T *r_data);

        template <typename T>
        typename Store<T>::Elem Get(MD5SUM key);

    private:
        template <typename T>
        Store<T> getStore();

    private:
        Store<Image> m_image_store;
    };
}

#endif