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
}