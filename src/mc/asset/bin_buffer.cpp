#include <fstream>
#include <sstream>
#include <iostream>

#include <mc/asset/bin_buffer.h>

namespace mc::asset
{
    BinBuffer::BinBuffer(const std::string &file_path) : m_file_path{file_path}
    {
        std::ifstream t(file_path.data());
        std::stringstream buffer;
        buffer << t.rdbuf();
        m_data = buffer.str();
    }
    BinBuffer::~BinBuffer()
    {
        std::cout << "BinBuffer::~BinBuffer" << std::endl;
    }
}