#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include <mc/csv.h>

namespace mc::tools
{
    template <typename T, typename U, typename W>
    void CSVReader<T, U, W>::Read(const char *file_path, std::vector<T> &v_data, std::vector<U> &e_data, std::vector<W> &s_data)
    {
        std::ifstream t(file_path);
        //
        std::string row;
        std::string col;
        int read_mode{0};
        while (std::getline(t, row))
        {
            if (row.find("#ebo") != std::string::npos)
            {
                read_mode = 1;
                continue;
            }
            else if (row.find("#specify") != std::string::npos)
            {
                read_mode = 2;
                continue;
            }
            if (std::size(row) <= 1)
            {
                continue;
            }
            //
            switch (read_mode)
            {
            case 0: // vertices
            {
                std::stringstream row_stream{row};
                while (std::getline(row_stream, col, ','))
                {
                    v_data.push_back(std::stof(col));
                }
            }
            break;
            case 1: // ebo
            {
                std::stringstream row_stream{row};
                while (std::getline(row_stream, col, ','))
                {
                    e_data.push_back(std::stoi(col));
                }
            }
            break;
            case 2: // specify
            {
                std::stringstream row_stream{row};
                while (std::getline(row_stream, col, ','))
                {
                    s_data.push_back(std::stoi(col));
                }
            }
            break;
            default:
                break;
            }
        }
    }
}