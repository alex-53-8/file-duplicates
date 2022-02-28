#ifndef CLI_CLI_H
#define CLI_CLI_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

namespace cli {

    enum ComparingMode {
        hash, name
    };
    ostream& operator << (ostream &os, ComparingMode &mode);

    struct Parameters {
        string version;
        string author;
        string commandName;
        int argc;
        char** argv;
    };

    struct Arguments {
        vector<string> folders;
        ComparingMode mode;
        string pattern;
        regex fileNamePattern;
    };
    ostream& operator << (ostream &os, Arguments &args);

    class CliException {
        private:
            string errorDescription;

        public:
            CliException(string error) : errorDescription{ error }
            {}

            string_view getError() const { return errorDescription; }
    };

    class ExitException {
    public:
        ExitException(){}
    };
    
    cli::Arguments parse(Parameters &params);

}

#endif
