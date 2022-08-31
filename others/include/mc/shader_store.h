#ifndef MC_SHADER_STORE_H
#define MC_SHADER_STORE_H

#include <unordered_map>
#include <memory>

#include <mc/shader.h>

namespace mc::low
{
    using ShaderP = std::shared_ptr<Shader>;
    using ShaderHash = std::unordered_map<int, ShaderP>;
    using RangeFunc = bool (*)(int, Shader *);

    class ShaderStore
    {
        static int s_id;
        ShaderHash m_store;

    public:
        // Constructors
        ShaderStore() = default;
        ShaderStore(const ShaderStore &other) = delete;            // 禁止拷贝构建
        ShaderStore &operator=(const ShaderStore &other) = delete; // 禁止拷贝赋值

    public:
        void Register(Shader *shader);
        ShaderP Get(int key);
        void Range(RangeFunc rf);
    };
}
#endif