#include "ReadFile.h"

util::filedata util::readFile(const char *path) {
    filedata data;
    data.file_path = path;
    
    FILE *f = fopen(path, "rb");
    if(!f) {
        std::cout << "[ERROR] Could not open file: " << path << std::endl;
        return data;
    }

    fseek(f, 0, SEEK_END);
    data.file_size = ftell(f);
    data.file_data = (char*) malloc(data.file_size + 1);
    fseek(f, 0, SEEK_SET);

    int b = fread(data.file_data, 1, data.file_size, f);
    data.file_data[data.file_size] = 0;

    if(b < data.file_size) {
        std::cout << "[ERROR] Not enough bytes read!" << std::endl;
        free(data.file_data);
        return {path, 0, nullptr};
    }

    return data;
}