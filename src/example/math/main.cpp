#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <mc/glmex/show.h>

namespace
{
    /**
     * testPerspective
     * * 用来测试透视矩阵的变换效果，观察w分量的影响
     */
    void testPerspective()
    {
        auto proj = glm::perspective(glm::radians(60.0f), 1.0f, 1.0f, 100.f);
        mc::glmex::showMat(proj);
        // 定一个z,观察 xy w
        // {
        //     // 结论1：xy 就很线性的从 -1 变到 1，超出部分依然是线性的
        //     glm::vec4 ve{1.0f, 0.0f, -20.0f, 1.0f};
        //     glm::vec4 res;
        //     for (auto x = -100.0f; x <= 100.0f; x += 0.1f)
        //     {
        //         ve.x = x;
        //         res = proj * ve;
        //         std::cout << "input x: " << x << std::endl;
        //         std::cout << "        ";
        //         mc::glmex::showVec(res);
        //         res.x /= res.w;
        //         res.y /= res.w;
        //         res.z /= res.w;
        //         res.w /= res.w;
        //         std::cout << "        ";
        //         mc::glmex::showVec(res);
        //     }
        // }
        {
            // 定xy = 0，观察z和w
            glm::vec4 input{0.0f, 0.0f, 0.0f, 1.0f};
            glm::vec4 res;

            for (auto z = -0.01f; z >= -110.f; z -= 0.1f)
            {
                input.z = z;
                res = proj * input;
                std::cout << "input z: " << z << std::endl;
                std::cout << "        ";
                mc::glmex::showVec(res);
            }
        }
    }
}

namespace game::example_list::math
{
    int Main()
    {
        testPerspective();
        return 0;
    }
}
