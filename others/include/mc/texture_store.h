#ifndef MC_TEXTURE_STORE_H
#define MC_TEXTURE_STORE_H

#include <unordered_map>
#include <memory>

#include <mc/texture.h>

namespace mc::low
{
    using TextureP = std::shared_ptr<Texture>;
    using TextureHash = std::unordered_map<int, TextureP>;
    using RangeTextureStoreFunc = bool (*)(int, Texture *);

    class TextureStore
    {
        static int s_id;
        TextureHash m_store;

    public:
        // Constructors
        TextureStore() = default;
        TextureStore(const TextureStore &other) = delete;            // 禁止拷贝构建
        TextureStore &operator=(const TextureStore &other) = delete; // 禁止拷贝赋值

    public:
        void Register(Texture *texture);
        TextureP Get(int key);
        void Range(RangeTextureStoreFunc rf);
    };
}
#endif