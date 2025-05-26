#include <iostream>
#include <locale>

using namespace std;

int	main(int argc, char **argv)
{
    auto loc = cin.getloc();
    cout << "defaut locale:" << loc.name() << endl;
    cout.imbue(locale("")); // 使用系统默认语言环境
    auto cloc = cout.getloc();
    cout << "cout locale:" << cloc.name() << "测试" << endl;
    // cout.imbue(locale("zh_CN.GB2312"));
    cloc = cout.getloc();
    return 0;
}
