#ifndef MC_ASSET_STORE_H
#define MC_ASSET_STORE_H

#include <unordered_map>
#include <memory>

#include <mc/asset/md5sum.h>

namespace mc::asset
{

    template <class T>
    class Store
    {
    public:
        using Elem = std::shared_ptr<T>;
        using THash = std::unordered_map<MD5SUM, Elem, MD5SUMHasher>;

    public:
        // Constructors
        Store() = default;
        Store(const Store &other) = delete;            // 禁止拷贝构建
        Store &operator=(const Store &other) = delete; // 禁止拷贝赋值

    public:
        void Register(MD5SUM key, T *data);
        Elem Get(MD5SUM key = MD5SUM{});
        void Del(MD5SUM key);

    private:
        THash m_store;
    };
}

#include <mc/asset/store.inl>

#endif