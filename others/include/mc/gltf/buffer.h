#ifndef MC_GLTF_BUFFER_H
#define MC_GLTF_BUFFER_H

#include <vector>
#include <string>

#include <mc/comm/gltf.pb.h>

namespace mc::gltf
{
    class Buffer
    {
        std::vector<unsigned char> m_data;

    public:
        Buffer(const std::string_view uri, int byteLength);

    public:
        void Show();
    };

    class BufferList
    {
        std::vector<Buffer> m_data;

    public:
        BufferList(const mc::comm::GLTF &gltf);

    public:
        void Show();
    };
}
#endif
