#include <iostream>
#include <string>

#include <glm/glm.hpp>

// game headers

// comm headers

namespace
{
    int castInt(float *input)
    {
        return reinterpret_cast<int *>(input)[0];
    }
    void testVec3Compare()
    {
        float one{1.0f};
        float a{0.1f};
        float sum{0.0f};
        for (int index = 0; index < 10; ++index)
        {
            sum += a;
        }
        std::cout << sum << " " << castInt(&sum) << std::endl;
        std::cout << one << " " << castInt(&one) << std::endl;
        std::cout << (one == sum) << std::endl;
        ///////////
        glm::vec3 foo{0.1f, 1.0f, 1.0f};
        glm::vec3 bar{1.0f, 1.0f, 1.0f};
        for (int index = 0; index < 10; ++index)
        {
            foo.x += 0.1f;
        }
        //
        std::cout << (foo == bar) << std::endl;
    }
}

namespace game::example_list::protobuf_test
{
    int Main()
    {
        testVec3Compare();
        return 0;
    }
}
