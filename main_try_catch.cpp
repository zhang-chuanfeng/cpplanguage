#include <iostream>

using namespace std;
int main()
try
{
    cout << "hello world\n";
    return 0;
}
catch (const exception &e)
{
    cerr << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops: unknown exception!\n";
    return 2;
}