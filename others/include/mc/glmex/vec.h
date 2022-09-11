#ifndef MC_GLMEX_VEC_H
#define MC_GLMEX_VEC_H

#include <glm/glm.hpp>

namespace mc::glmex
{
    // result = vec4 + vec3
    inline void AddInPlace(glm::vec4 &input, const glm::vec3 &other)
    {
        input.x += other.x;
        input.y += other.y;
        input.z += other.z;
    }
}

#endif
