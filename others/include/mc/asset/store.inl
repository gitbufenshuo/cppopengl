#include <utility>

#include <mc/asset/store.h>

namespace mc::asset
{

    template <class T>
    void Store<T>::Register(MD5SUM key, T *data)
    {
        m_store.insert(std::pair{key, Elem{data}});
    }

    template <class T>
    Store<T>::Elem Store<T>::Get(MD5SUM key)
    {
        return m_store[key];
    }

}