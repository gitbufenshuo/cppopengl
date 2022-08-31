#include <utility>

#include <mc/shader_store.h>

namespace mc::low
{
    int ShaderStore::s_id{0};
    //
    void ShaderStore::Register(Shader *shader)
    {
        ++s_id;
        m_store.insert(std::pair{s_id, ShaderP{shader}});
    }
    ShaderP ShaderStore::Get(int key)
    {
        return m_store[key];
    }
    void ShaderStore::Range(RangeFunc rf)
    {
        for (const auto &n : m_store)
        {
            if (rf(n.first, n.second.get()))
            {
                continue;
            }
            break;
        }
    }
}