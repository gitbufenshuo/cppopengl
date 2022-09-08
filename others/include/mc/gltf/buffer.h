#ifndef MC_GLTF_BUFFER_H
#define MC_GLTF_BUFFER_H

#include <vector>
#include <string>
#include <string_view>

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
        void *Offset(int index) const;
    };

    class BufferList
    {
        std::vector<Buffer> m_data;

    public:
        BufferList(const mc::comm::GLTF &gltf);

    public:
        void Show();
        const Buffer &GetBuffer(int index) const;
    };

    class BufferView
    {
        unsigned int m_gl_id{0}; // vbo vao ebo
        const mc::comm::BufferView &m_bufferView;

    public:
        BufferView(const mc::comm::BufferView &bufferView);
        void SetGLID(unsigned int gl_id);
        unsigned int GetGLID() const;
    };

    class BufferViewList
    {
        std::vector<BufferView> m_data;

    public:
        BufferViewList(const mc::comm::GLTF &gltf);
        const BufferView &GetBufferView(int index) const;
    };

    class Accessor
    {
        const mc::comm::Accessor &m_data;

    public:
        Accessor(const mc::comm::Accessor &data);

    public:
        static int GetSizeFromType(std::string_view _type);
    };

    class AccessorList
    {
        std::vector<Accessor> m_data;

    public:
        AccessorList(const mc::comm::GLTF &gltf);
    };
}

namespace mc::gltf
{

    class GLTF
    {
        const mc::comm::GLTF &m_gltf;
        AccessorList m_aclist;
        BufferList m_blist;
        BufferViewList m_bvlist;

    public:
        GLTF(const mc::comm::GLTF &gltf);

    public:
        const mc::comm::GLTF &GetCommGLTF() const;
        const Buffer &GetBuffer(int index) const;
        const BufferView &GetBufferView(int index) const;
    };
}

#endif
