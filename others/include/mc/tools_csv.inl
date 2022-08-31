#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

#include <mc/csv.h>

namespace mc::tools
{

    template <typename T>
    T sto(std::string &input)
    {
        return sto(input, the_type<T>());
    }
    inline float sto(std::string &input, the_type<float>)
    {
        return std::stof(input);
    }
    inline float sto(std::string &input, the_type<int>)
    {
        return std::stoi(input);
    }

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
                    v_data.push_back(sto<T>(col));
                }
            }
            break;
            case 1: // ebo
            {
                std::stringstream row_stream{row};
                while (std::getline(row_stream, col, ','))
                {
                    e_data.push_back(sto<U>(col));
                }
            }
            break;
            case 2: // specify
            {
                std::stringstream row_stream{row};
                while (std::getline(row_stream, col, ','))
                {
                    s_data.push_back(sto<W>(col));
                }
            }
            break;
            default:
                break;
            }
        }
    }
    template <typename T, typename U, typename W>
    void CSVReader<T, U, W>::ReadMaterial(const char *file_path, std::vector<T> &data)
    {
        std::ifstream t(file_path);
        //
        std::string row;
        std::string col;
        //
        while (std::getline(t, row))
        {
            if (row.size() <= 1)
            {
                continue; // 空行
            }
            if (row[0] == '#')
            {
                continue; // 注释行
            }
            //
            std::stringstream row_stream{row};
            while (std::getline(row_stream, col, ','))
            {
                data.push_back(sto<T>(col));
            }
        }
    }
    template <typename T, typename U, typename W>
    void CSVReader<T, U, W>::ReadMultiMaterial(const char *file_path, std::unordered_map<int, T> &m_data)
    {
        std::ifstream t(file_path);
        //
        std::string row;
        std::string col;
        //
        int key = -1;
        std::string m_name;
        std::vector<float> _data_holder;
        _data_holder.reserve(10);
        //
        while (std::getline(t, row))
        {
            if (row.size() <= 1)
            {
                continue; // 空行
            }
            if (row[0] == '#')
            {
                if (key > -1)
                {
                    m_data.insert(std::pair{key, T{new W{_data_holder, m_name}}});
                }
                _data_holder.resize(0);
                ++key;
                std::stringstream row_stream{row};
                int loop = 0;
                while (std::getline(row_stream, col, '='))
                {
                    if (loop == 1)
                    {
                        m_name = col;
                        break;
                    }
                    // data.push_back(sto<T>(col));
                    loop++;
                }
                continue; // 注释行
            }
            std::stringstream row_stream{row};
            while (std::getline(row_stream, col, ','))
            {
                _data_holder.push_back(sto<U>(col));
            }
        }
    }
}