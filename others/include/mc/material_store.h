#ifndef MC_MATERIAL_STORE_H
#define MC_MATERIAL_STORE_H

#include <unordered_map>
#include <memory>

#include <mc/material.h>

namespace mc::low
{
    using MaterialP = std::shared_ptr<Material>;
    using MaterialHash = std::unordered_map<int, MaterialP>;
    using RangeMaterialStoreFunc = bool (*)(int, Material *);

    class MaterialStore
    {
        static int s_id;
        MaterialHash m_store;

    public:
        // Constructors
        MaterialStore() = default;
        MaterialStore(const MaterialStore &other) = delete;            // 禁止拷贝构建
        MaterialStore &operator=(const MaterialStore &other) = delete; // 禁止拷贝赋值

    public:
        void Register(Material *material);
        MaterialP Get(int key);
        int GetCount();
        void Range(RangeMaterialStoreFunc rf);
        void LoadFromFile(const char *file_name, Material::MaterialType ma_type);
    };
}
#endif