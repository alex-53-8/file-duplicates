#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "utils.h"

using std::vector;
using std::string;


namespace utils {
namespace str {
    vector<string> split (string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }

    string toString(vector<string> v, char delimiter) {
        std::ostringstream oss;
        if (!v.empty()) {
            unsigned int i = 0;
            for (; i < v.size() - 1; i++) {
                oss << v[i] << delimiter;
            }
            oss << v[i];
        }

        return oss.str();
    }
}
}
