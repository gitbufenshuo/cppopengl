#ifndef MC_ASSET_ASSET_MANAGER_H
#define MC_ASSET_ASSET_MANAGER_H

#include <mc/asset/store.h>
#include <mc/asset/image.h>

namespace mc::asset
{
    class AssetStore
    {
    public:
    private:
        Store<Image> m_image_store;
    };
}

#endif