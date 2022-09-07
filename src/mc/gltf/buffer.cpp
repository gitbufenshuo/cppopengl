#include <string_view>
#include <iostream>

#include <mc/tools/base64.h>
#include <mc/gltf/buffer.h>
#include <mc/comm/gltf.pb.h>

namespace mc::gltf
{
    Buffer::Buffer(std::string_view uri, int byteLength)
    {
        int index = uri.find("base64,");
        if (index >= 0)
        {
            m_data.reserve(byteLength);
            uri.remove_prefix(index + 7);
            mc::tools::Base64::Decode(uri, m_data);
            return;
        }
        std::cout << " buffer type invalid " << std::endl;
    }
    void Buffer::Show()
    {
        std::cout << "length: " << m_data.size() << std::endl;
    }
    void *Buffer::Offset(int index) const
    {
        const unsigned char *pr{m_data.data()};
        const void *cv{static_cast<const void *>(pr)};
        return const_cast<void *>(cv);
    }

    //

    BufferList::BufferList(const mc::comm::GLTF &gltf)
    {
        int buffer_count = gltf.buffers_size();
        for (int index = 0; index < buffer_count; ++index)
        {
            auto &onebuffer{gltf.buffers(index)};
            m_data.push_back(
                Buffer{std::string_view{onebuffer.uri()}, onebuffer.bytelength()});
        }
    }
    void BufferList::Show()
    {
        for (auto &one : m_data)
        {
            one.Show();
        }
    }
    const Buffer &BufferList::GetBuffer(int index) const
    {
        return m_data[index];
    }
}

namespace mc::gltf
{
    BufferView::BufferView(const mc::comm::BufferView &bufferView) : m_bufferView{bufferView}
    {
    }
    void BufferView::SetGLID(unsigned int gl_id)
    {
        m_gl_id = gl_id;
    }
    unsigned int BufferView::GetGLID() const
    {
        return m_gl_id;
    }

    BufferViewList::BufferViewList(const mc::comm::GLTF &gltf)
    {
        int bv_count = gltf.bufferviews_size();
        for (int index = 0; index < bv_count; ++index)
        {
            auto &onebv{gltf.bufferviews(index)};
            m_data.push_back(BufferView{onebv});
        }
    }
    const BufferView &BufferViewList::GetBufferView(int index) const
    {
        return m_data[index];
    }

}

namespace mc::gltf
{
    Accessor::Accessor(const mc::comm::Accessor &data) : m_data{data}
    {
    }
    AccessorList ::AccessorList(const mc::comm::GLTF &gltf)
    {
        int ac_count = gltf.accessors_size();
        for (int index = 0; index < ac_count; ++index)
        {
            auto &oneac{gltf.accessors(index)};
            m_data.push_back(Accessor{oneac});
        }
    }
    // static
    int Accessor::GetSizeFromType(std::string_view _type)
    {
        if (_type.find("VEC3") == 0)
        {
            return 3;
        }
        if (_type.find("VEC2") == 0)
        {
            return 2;
        }
        if (_type.find("SCALAR") == 0)
        {
            return 1;
        }
        return 0;
    }
}

namespace mc::gltf
{
    GLTF::GLTF(const mc::comm::GLTF &gltf) : m_gltf{gltf}, m_aclist{gltf}, m_blist{gltf}, m_bvlist{gltf}
    {
    }
    const mc::comm::GLTF &GLTF::GetCommGLTF() const
    {
        return m_gltf;
    }
    const Buffer &GLTF::GetBuffer(int index) const
    {
        return m_blist.GetBuffer(index);
    }
    const BufferView &GLTF::GetBufferView(int index) const
    {
        return m_bvlist.GetBufferView(index);
    }

}