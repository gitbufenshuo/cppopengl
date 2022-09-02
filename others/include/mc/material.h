#ifndef MC_LOW_MATERIAL_H
#define MC_LOW_MATERIAL_H

#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include <mc/texture_store.h>
#include <mc/shader_store.h>

namespace mc::low
{
    class Engine;
    class GameObject;

    class Material
    {
    public:
        virtual void PostUniform(Engine *eg, GameObject *gb) = 0;
        virtual void SetShader(ShaderP shader) = 0;
        virtual void AddTexture(TextureP texture) = 0;
        virtual void ShowMe() = 0;
        virtual ~Material() = default;
    };
}
#endif