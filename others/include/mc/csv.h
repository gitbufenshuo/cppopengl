#ifndef MC_TOOLS_CSV_H
#define MC_TOOLS_CSV_H

#include <vector>

namespace mc::tools
{
    template <typename T, typename U, typename W>
    class CSVReader
    {
    public:
        static void Read(const char *file_path, std::vector<T> &m_v_data, std::vector<U> &m_e_data, std::vector<W> &m_s_data);
    };
}

#include <mc/tools_csv.inl>
#endif