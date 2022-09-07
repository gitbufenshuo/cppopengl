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

    class BufferView
    {
        unsigned int m_gl_id{0}; // vbo vao ebo
        const mc::comm::BufferView &m_bufferView;

    public:
        BufferView(const mc::comm::BufferView &bufferView);
    };

    class BufferViewList
    {
        std::vector<BufferView> m_data;

    public:
        BufferViewList(const mc::comm::GLTF &gltf);
    };

    class Accessor
    {
        const mc::comm::Accessor &m_data;

    public:
        Accessor(const mc::comm::Accessor &data);
    };

    class AccessorList
    {
        std::vector<Accessor> m_data;

    public:
        AccessorList(const mc::comm::GLTF &gltf);
    };
}
#endif
