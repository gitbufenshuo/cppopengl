#ifndef MC_GLMEX_SHOW_H
#define MC_GLMEX_SHOW_H

#include <iostream>
#include <glm/glm.hpp>

namespace mc::glmex
{
    inline void showMat(const glm::mat4 &input)
    {
        std::cout << "---show mat---" << std::endl;
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                std::cout << input[col][row] << " ";
            }
            std::cout << std::endl;
        }
    }
    inline void showVec(const glm::vec4 &input)
    {
        std::cout << "---show vec---" << std::endl;
        std::cout << input.x << ", "
                  << input.y << ", "
                  << input.z << ", "
                  << input.w << std::endl;
    }

}

#endif
