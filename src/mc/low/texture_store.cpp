#include <utility>

#include <mc/texture_store.h>

namespace mc::low
{
    int TextureStore::s_id{0};
    //
    void TextureStore::Register(Texture *texture)
    {
        ++s_id;
        m_store.insert(std::pair{s_id, TextureP{texture}});
    }
    TextureP TextureStore::Get(int key)
    {
        return m_store[key];
    }
    void TextureStore::Range(RangeTextureStoreFunc rf)
    {
        for (const auto &n : m_store)
        {
            if (rf(n.first, n.second.get()))
            {
                continue;
            }
            break;
        }
    }
}