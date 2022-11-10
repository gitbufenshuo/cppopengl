#ifndef MC_TOOLS_FILES_H
#define MC_TOOLS_FILES_H
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

namespace mc::tools
{
    class Files
    {
    public:
        static void WriteFile(const std::string &filepath, unsigned char *buffer, int size)
        {
            // open a file
            int fd = open(filepath.data(), O_RDWR | O_CREAT, 00777);
            //  lseek moves the file pointer backward by file_size-1 bit
            lseek(fd, size - 1, SEEK_END);
            //  Write a null character from the pointer; mmap cannot extend the file length, which is equivalent to pre-setting the file length and preparing an empty shelf
            write(fd, "", 1);
            //  Use mmap function to establish memory mapping
            char *addr = (char *)mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            //  The memory map is established, and the file can be closed at this time
            close(fd);
            //  Copy data to addr
            memcpy(addr, buffer, size);
            //  Unmap
            munmap(addr, size);
        }
    };
} // namespace mc::tools

#endif