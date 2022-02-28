#include <iostream>
#include <functional>
#include <map>
#include <vector>

#include "files.h"
#include "cli.h"

namespace fs = filesystem;
using namespace std;

cli::Arguments arguments(int argc, char** argv) {
    cli::Parameters params = {CLI_VERSION, CLI_AUTHOR, CLI_COMMAND_NAME, argc, argv};
    cli::Arguments args = cli::parse(params);

    cout << endl << "Performing search by following arguments:" << endl;
    cout << args << endl;

    return args;
}

string getFileHash(cli::ComparingMode &mode, const fs::path& file) {
    if (mode == cli::ComparingMode::hash) {
        return files::contentHash(file);
    } else {
        return file.filename();
    }
}

void discover(cli::Arguments& arguments) {
    map<string, vector<fs::path>> storage;

    function<void(const fs::path&)> consumer = [&storage, &arguments](const fs::path& file) mutable {
        try {
            string hash = getFileHash(arguments.mode, file);
            if (storage.count(hash)) {
                storage.at(hash).push_back(file);
            } else {
                vector<fs::path> list{file};
                storage[hash] = list;
            }
        } catch(files::FileReadException e) {
            cerr << "cannot open a file: " << fs::canonical(file) << endl;
        }
    };

    for(string directory: arguments.folders) {
        files::iterate(directory, arguments.fileNamePattern, consumer);
    }

    for (const auto& [hash, list] : storage) {
        if(list.size() > 1) {
            cout << "Same files for a " << arguments.mode << ": " << hash << endl;
            for(auto item : list) {
                cout << "  " << fs::canonical(item).string() << endl;
            }
        }
    }
}

int main(int argc, char** argv) {
    try {
        cli::Arguments args = arguments(argc, argv);
        discover(args);
    } catch(cli::CliException e) {
        cerr << e.getError() << endl;
    } catch(cli::ExitException e) {

    }

    return 0;
}
