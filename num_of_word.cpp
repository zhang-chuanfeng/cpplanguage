#include <iostream>
#include <string>
#include <map>

using namespace std;
int	main(int argc, char *argv[])
{
    string buf;
    map<string,int> word;
    while (cin>>buf) ++word[buf];

    for (const auto & pair : word)
        cout << "{" << pair.first << "," << pair.second << "}" << endl;

    return 0;
}