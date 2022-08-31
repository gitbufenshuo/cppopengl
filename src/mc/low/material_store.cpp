#include <utility>

#include <mc/material_store.h>
#include <mc/csv.h>

namespace mc::low
{
    int MaterialStore::s_id{0};
    //
    void MaterialStore::Register(Material *material)
    {
        ++s_id;
        m_store.insert(std::pair{s_id, MaterialP{material}});
    }
    MaterialP MaterialStore::Get(int key)
    {
        return m_store[key];
    }
    int MaterialStore::GetCount()
    {
        return static_cast<int>(m_store.size());
    }
    void MaterialStore::Range(RangeMaterialStoreFunc rf)
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
    void MaterialStore::LoadFromFile(const char *file_name)
    {
        mc::tools::CSVReader<MaterialP, float, Material>::ReadMultiMaterial(file_name, m_store);
    }
}