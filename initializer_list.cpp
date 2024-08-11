#include <iostream>
#include <string>
#include <vector>

// 函数参数

using namespace std;

vector<string> arguments(int argc, char* argv[]) {
    vector<string> res;
    for (int i = 0; i != argc; ++i)
        res.push_back(argv[i]);
    return res;
}

void error(int severity, const vector<string> err) {
    for (auto& s : err) {
        cerr << s << ' ';
    }
    cerr << '\n';
    if (!severity) exit(-1);
}

int main(int argc, char* argv[]) {
    auto args = arguments(argc, argv);
    error((args.size()<2)?0:1, args);
    cout << "main test\n";
    return 0;
}