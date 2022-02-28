#include <string>
#include <iostream>
#include <filesystem>
#include <functional>
#include <regex>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>

#include "files.h"

namespace fs = std::filesystem;
using namespace std;

namespace files {
    
    string contentHash(const fs::path& file) {
        ifstream source(file, ios::in | ios::binary);
        if (!source.good()) {
            throw FileReadException();
        }

        constexpr const std::size_t buffer_size { 1 << 12 };
        char buffer[buffer_size];
        unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

        SHA256_CTX ctx;
        SHA256_Init(&ctx);

        while (source.good()) {
          source.read(buffer, buffer_size);
          SHA256_Update(&ctx, buffer, source.gcount());
        }

        SHA256_Final(hash, &ctx);
        source.close();

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');

        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
          oss << std::setw(2) << static_cast<unsigned int>(hash[i]);
        }

        return oss.str();
    }

    void iterate(fs::path path, regex pattern, function<void(const fs::path& file)>& consumer) {
        fs::recursive_directory_iterator iterator;
        try {
            iterator = fs::recursive_directory_iterator{path};
        } catch(fs::filesystem_error e) {
            cerr << "cannot open a directory: " << path << std::endl;
            return;
        }

        for (const fs::directory_entry &entry : iterator) {
            if (entry.is_regular_file()) {
                string name = entry.path().filename();

                if (regex_match(name, pattern)) {
                    consumer(entry.path());
                }
            }
        }
    }

    void iterate(string path, regex pattern, function<void(const fs::path& file)>& consumer) {
        iterate(fs::path{path}, pattern, consumer);
    }

}
