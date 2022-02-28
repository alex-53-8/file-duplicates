#ifndef FILES_FILES_H
#define FILES_FILES_H

#include <string>
#include <iostream>
#include <filesystem>
#include <functional>
#include <regex>

namespace fs = std::filesystem;
using namespace std;

namespace files {

    class FileReadException {
    public:
        FileReadException(){}
    };

    void iterate(fs::path path, regex pattern, function<void(const fs::path& file)>& consumer);
    
    void iterate(string path, regex pattern, function<void(const fs::path& file)>& consumer);
    
    string contentHash(const fs::path& file);

}

#endif
