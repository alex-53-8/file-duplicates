#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

#include "cli.h"

using std::string;

TEST_CASE("cli::parse", ""){

    int argc = 7;
    char** argv = new char*[argc];
    argv[0] = "cmd";
    argv[1] = "-m";
    argv[2] = "name";
    argv[3] = "-p";
    argv[4] = ".*\\.api";
    argv[5] = "-f";
    argv[6] = "f1:f2:f3:f4";

    cli::Parameters params = {"1.0.0", "author", "cmd", argc, argv};
    cli::Arguments result = cli::parse(params);

    REQUIRE(result.pattern.compare(".*\\.api") == 0);
    REQUIRE(result.mode == cli::ComparingMode::name);
    vector<string> folders{"f1", "f2", "f3", "f4"};
    REQUIRE(result.folders == folders);
}

