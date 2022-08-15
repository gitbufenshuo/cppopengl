#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include <mc/csv.h>

namespace mc::tools
{
    template <typename T>
    void CSVReader<T>::Read(const char *file_path, std::vector<T> &m_data)
    {
        std::ifstream t(file_path);
        //
        std::string row;
        std::string col;
        while (std::getline(t, row))
        {
            if (std::size(row) <= 1)
            {
                continue;
            }
            //
            std::stringstream row_stream{row};
            while (std::getline(row_stream, col, ','))
            {
                m_data.push_back(std::stof(col));
            }
        }
        std::cout << file_path << " has " << std::size(m_data) << std::endl;
    }
}