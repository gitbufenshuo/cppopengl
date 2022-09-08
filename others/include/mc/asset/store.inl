#include <utility>

#include <mc/asset/store.h>

namespace mc::asset
{

    template <class T>
    void Store<T>::Register(MD5SUM key, T *shader)
    {
        m_store.insert(std::pair{s_id, ShaderP{shader}});
    }

    template <class T>
    Store<T>::Elem Store<T>::Get(MD5SUM key)
    {
        return m_store[key];
    }

}