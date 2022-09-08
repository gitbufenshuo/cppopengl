#ifndef MC_MODEL_STORE_H
#define MC_MODEL_STORE_H

#include <unordered_map>
#include <memory>

#include <mc/model.h>

namespace mc::low
{
    using ModelP = std::shared_ptr<Model>;
    using ModelHash = std::unordered_map<int, ModelP>;
    using RangeModelStoreFunc = bool (*)(int, Model *);

    class ModelStore
    {
        static int s_id;
        ModelHash m_store;

    public:
        // Constructors
        ModelStore() = default;
        ModelStore(const ModelStore &other) = delete;            // 禁止拷贝构建
        ModelStore &operator=(const ModelStore &other) = delete; // 禁止拷贝赋值

    public:
        void Register(Model *Model);
        ModelP Get(int key = -1);
        void Range(RangeModelStoreFunc rf);
    };
}
#endif