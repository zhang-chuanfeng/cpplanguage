// 1. **regex_match**
// - 要求整个字符串完全匹配模式
// - 如果字符串中只有部分匹配则返回false
// - 常用于验证整个字符串是否符合特定格式

// 2. **regex_search**
// - 在字符串中查找第一个匹配的子串
// - 只要找到一个匹配就返回true
// - 常用于在文本中搜索特定模式

// 3. **regex_replace**
// - 替换所有匹配的子串
// - 可以使用格式化字符串或替换函数
// - 常用于文本转换和格式化

#include <iostream>
#include <regex>
#include <string>

using namespace std;

void test_regex_match()
{
    cout << "\n=== regex_match 测试 ===\n";
    regex pattern(R"(\w+@\w+\.\w+)"); // 简单的邮箱格式

    string test1 = "user@example.com";
    string test2 = "invalid email user@example.com extra";

    cout << "测试字符串1: " << test1 << " - ";
    cout << (regex_match(test1, pattern) ? "匹配" : "不匹配") << '\n';

    cout << "测试字符串2: " << test2 << " - ";
    cout << (regex_match(test2, pattern) ? "匹配" : "不匹配") << '\n';
}

void test_regex_search()
{
    cout << "\n=== regex_search 测试 ===\n";
    regex pattern(R"(\w+@\w+\.\w+)");
    string text = "联系方式: user@example.com 或 admin@example.com";

    smatch matches;
    string::const_iterator searchStart(text.cbegin());

    while (regex_search(searchStart, text.cend(), matches, pattern))
    {
        cout << "找到匹配: " << matches[0] << '\n';
        searchStart = matches.suffix().first;
    }
}

void test_regex_replace()
{
    cout << "\n=== regex_replace 测试 ===\n";

    // 替换日期格式 yyyy-mm-dd 到 dd/mm/yyyy
    regex date_pattern(R"((\d{4})-(\d{2})-(\d{2}))");
    string text = "开始日期: 2023-05-20, 结束日期: 2023-12-31";

    string result = regex_replace(text, date_pattern, "$3/$2/$1");
    cout << "原文: " << text << '\n';
    cout << "替换后: " << result << '\n';

    // 手动遍历并自定义替换
    string result2;
    auto start = text.cbegin();
    auto end = text.cend();
    smatch m;
    while (regex_search(start, end, m, date_pattern))
    {
        result2.append(m.prefix().first, m.prefix().second);
        result2 += m[3].str() + "/" + m[2].str() + "/" + m[1].str();
        start = m.suffix().first;
    }
    result2.append(start, end);
    cout << "使用自定义逻辑替换: " << result2 << '\n';
}

int main()
{
    test_regex_match();
    test_regex_search();
    test_regex_replace();
    return 0;
}