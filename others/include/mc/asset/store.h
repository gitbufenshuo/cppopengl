#ifndef MC_ASSET_STORE_H
#define MC_ASSET_STORE_H

#include <cstddef>
#include <unordered_map>
#include <memory>

namespace mc::asset
{
    struct MD5SUM
    {
        // 经典的md5的结果是 16字节
        // 展示的时候使用 hex 编码，变成32字节
        unsigned char data[16];
        bool operator==(const MD5SUM &other) const
        {
            auto t_base{reinterpret_cast<const unsigned long long *>(data)};
            auto o_base{reinterpret_cast<const unsigned long long *>(other.data)};
            return (t_base[0] == o_base[0]) && (t_base[1] == o_base[1]);
        }
    };

    struct MD5SUMHasher
    {
        std::size_t operator()(const MD5SUM &k) const
        {
            auto t_base{reinterpret_cast<const unsigned long long *>(k.data)};
            return t_base[0];
        }
    };

    template <class T>
    class Store
    {
    public:
        using Elem = std::shared_ptr<T>;
        using THash = std::unordered_map<MD5SUM, Elem>;

    public:
        // Constructors
        Store() = default;
        Store(const Store &other) = delete;            // 禁止拷贝构建
        Store &operator=(const Store &other) = delete; // 禁止拷贝赋值

    public:
        void Register(MD5SUM key, T *data);
        Elem Get(MD5SUM key);

    private:
        THash m_store;
    };
}

#include <mc/asset/store.inl>

#endif