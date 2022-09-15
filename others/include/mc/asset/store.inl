#include <utility>
#include <typeinfo>
// asset
#include <mc/asset/store.h>

namespace mc::asset
{

    template <class T>
    void Store<T>::Register(MD5SUM key, T *data)
    {
        m_store.insert(std::pair{key, Elem{data}});
    }

    template <class T>
    typename Store<T>::Elem Store<T>::Get(MD5SUM key)
    {
        auto it{m_store.find(key)};
        if (it == m_store.end())
        {
            std::cout << "[NOT FOUND] Store<T>::Get() " << typeid(T).name() << std::endl;
        }
        return m_store[key];
    }

    template <class T>
    void Store<T>::Del(MD5SUM key)
    {
        m_store.erase(key);
    }

}