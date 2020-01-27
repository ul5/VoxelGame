#include <fstream>
#include <iostream>

namespace util {

    typedef struct filedata {
        const char *file_path;
        size_t file_size;
        char *file_data;
    } filedata;

    extern filedata readFile(const char *path);

}