#ifndef MC_TOOLS_CSV_H
#define MC_TOOLS_CSV_H

#include <vector>
#include <unordered_map>

namespace mc::tools
{
    template <class T>
    struct the_type
    {
        using type = T;
    };

    template <typename T, typename U, typename W>
    class CSVReader
    {
    public:
        static void Read(const char *file_path, std::vector<T> &m_v_data, std::vector<U> &m_e_data, std::vector<W> &m_s_data);
        static void ReadMaterial(const char *file_path, std::vector<T> &m_data);
        static void ReadMultiMaterial(const char *file_path, std::unordered_map<int,T> &m_data);
    };
}

#include <mc/tools_csv.inl>
#endif