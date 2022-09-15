#include <utility>
#include <typeinfo>
// asset
#include <mc/asset/store.h>

namespace mc::asset
{

    template <class T>
    void Store<T>::Register(MD5SUM key, T *data)
    {
        std::cout << "[Store<T>::Register] "
                  << typeid(T).name() << " "
                  << data << " "
                  << std::endl;
        m_store.insert(std::pair{key, Elem{data}});
    }

    template <class T>
    typename Store<T>::Elem Store<T>::Get(MD5SUM key)
    {
        if (key == MD5SUM{})
        {
            auto it{m_store.begin()};
            key = it->first;
        }
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