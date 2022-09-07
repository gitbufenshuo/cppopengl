#include <utility>

#include <mc/model_store.h>

namespace mc::low
{
    int ModelStore::s_id{0};
    //
    void ModelStore::Register(Model *model)
    {
        ++s_id;
        m_store.insert(std::pair{s_id, ModelP{model}});
    }
    ModelP ModelStore::Get(int key)
    {
        if (key == -1)
        {
            // 获取最后一个
            return m_store[s_id];
        }
        return m_store[key];
    }
    void ModelStore::Range(RangeModelStoreFunc rf)
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