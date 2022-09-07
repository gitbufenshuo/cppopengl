#include <iostream>
#include <string>
#include <fstream>
// game headers

// comm headers
#include <mc/comm/gltf.pb.h>
#include <mc/gltf/buffer.h>

namespace
{
    void loadAndParse()
    {
        mc::comm::GLTF gltf;
        {
            std::ifstream file_stream("../others/resource/gltf/minimal.json.gltf.pb", std::ios::in | std::ios::binary);
            auto ok{gltf.ParseFromIstream(&file_stream)};
            if (!ok)
            {
                std::cout << "loading gltf.pb fail" << std::endl;
            }
        }
        mc::gltf::BufferList buffers{gltf};
        buffers.Show();
    }
}

namespace game::example_list::gltf_exp
{
    int Main()
    {
        loadAndParse();
        return 0;
    }
}
