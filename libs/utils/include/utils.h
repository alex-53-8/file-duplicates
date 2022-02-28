#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <iostream>
#include <string>

using std::vector;
using std::string;

namespace utils {
namespace str {
    vector<string> split (string s, string delimiter);
    string toString(vector<string> v, char delimiter);
}
}

#endif