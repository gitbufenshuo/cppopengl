#ifndef MC_ASSET_MD5SUM_H
#define MC_ASSET_MD5SUM_H

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <spdlog/fmt/ostr.h> // must be included

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
        MD5SUM()
        {
            std::fill(data, data + 16, 0);
        }
    };

    inline std::ostream &operator<<(std::ostream &cout, const MD5SUM &input)
    {
        std::cout << "0x" << std::hex;
        for (int index = 0; index < 16; ++index)
        {
            std::cout << static_cast<unsigned int>(input.data[index]);
        }
        std::cout << std::dec << std::endl;
        return cout;
    }

    struct MD5SUMHasher
    {
        std::size_t operator()(const MD5SUM &k) const
        {
            auto t_base{reinterpret_cast<const unsigned long long *>(k.data)};
            return t_base[0];
        }
    };
} // namespace mc::asset

#endif