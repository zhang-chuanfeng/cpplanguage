#include <iostream>
#include <regex>
#include <string>

using namespace std;
int main() {
    regex pat (R"(\w{2}\s*\d{5}(-\d{4}?))");
    int lineno = 0;
    for (string line;getline(cin, line);) {
        ++lineno;
        smatch matchs;
        if (regex_search(line,matchs, pat))
            cout << lineno << ":" << matchs[0] << endl;
    }

    return 0;
}