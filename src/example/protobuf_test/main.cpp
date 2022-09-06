#include <iostream>
#include <string>
// game headers

// comm headers
#include <mc/comm/transform.pb.h>

namespace
{
    void testProto()
    {
        mc::comm::Vec3 tr;
        tr.set_x(1.0f);
        tr.set_y(2.0f);
        tr.set_z(3.0f);
        std::string tr_data;
        tr.SerializePartialToString(&tr_data);
        std::cout << "Vec3 序列化: ";
        for (auto onebyte : tr_data)
        {
            std::cout << static_cast<int>(onebyte) << " ";
        }
        std::cout << std::endl;
    }
}

namespace game::example_list::protobuf_test
{
    int Main()
    {
        testProto();
        return 0;
    }
}
