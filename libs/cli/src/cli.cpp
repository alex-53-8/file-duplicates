#include <iostream>
#include <string>
#include <vector>
#include "cxxopts.hpp"

#include "cli.h"
#include "utils.h"

using namespace cxxopts;
using namespace std;

namespace cli {
    
    ostream& operator << (ostream &os, Arguments &args) {
        os << "> folders: " << endl << utils::str::toString(args.folders, '\n') << endl;
        os << "> comparing method: " << args.mode << endl;
        os << "> pattern: " << args.pattern << endl;
        return os;
    }

    ostream& operator << (ostream &os, ComparingMode &mode) {
        switch(mode) {
            case ComparingMode::hash: os << "hash"; break;
            case ComparingMode::name: os << "name";  break;
            default: {
                cerr << "An error occurred" << endl;
                os << "unknown type";
            }
        }

        return os;
    };

    void handleCompareMode(ParseResult &result, cli::Arguments &arguments) {
        if (result.count("compare-mode")) {
            string mode = result["compare-mode"].as<string>();
            if (mode.compare("name") == 0) {
                arguments.mode = cli::ComparingMode::name;
            } else {
                arguments.mode = cli::ComparingMode::hash;
            }
        }
    }

    void handleFileNamePattern(ParseResult &result, cli::Arguments &arguments) {
        if (result.count("pattern")) {
            arguments.pattern = result["pattern"].as<string>();
        } else {
            arguments.pattern = ".*";
        }

        try {
            arguments.fileNamePattern = regex(arguments.pattern);
        } catch(regex_error e) {
            throw CliException("Unable to compile a regex expression");
        }
    }

    void handleFolders(ParseResult &result, cli::Arguments &arguments) {
        if (result.count("folders")) {
            arguments.folders = utils::str::split(result["folders"].as<string>(), ":");
        } else {
            arguments.folders = {"."};
        }
    }

    cli::Arguments parse(Parameters &params) {
        Options options(params.commandName, "");

        options.add_options()
            ("h,help", "Print usage")
            ("f,folders", "folders where to look for duplicates; specify folders in format f1[:f2[:f3[:fn]]]; path of execution is used is used by default", cxxopts::value<string>())
            ("m,compare-mode", "supports comparing by \"hash\" or by \"name\". \"hash\" is used by default", cxxopts::value<string>())
            ("p,pattern", "regex for a file name, \".*\" is used by default", cxxopts::value<string>())
        ;

        ParseResult result = options.parse(params.argc, params.argv);

        if (result.count("help")) {
            cout << options.help() << endl;
            cout << "File duplicates " << params.version << ", " << params.author << endl;
            throw ExitException();
        }

        cli::Arguments arguments{};

        handleCompareMode(result, arguments);
        handleFileNamePattern(result, arguments);
        handleFolders(result, arguments);

        return arguments;
    }

}
