#include <iostream>
#include <regex>
#include <string>

using namespace std;

void parse_sip_message() {
    // 示例 SIP 消息
    string sip_message = 
        "INVITE sip:bob@biloxi.com SIP/2.0\r\n"
        "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhks\r\n"
        "Max-Forwards: 70\r\n"
        "To: Bob <sip:bob@biloxi.com>\r\n"
        "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n"
        "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n"
        "CSeq: 314159 INVITE\r\n"
        "Contact: <sip:alice@pc33.atlanta.com>\r\n"
        "Content-Type: application/sdp\r\n"
        "Content-Length: 0\r\n"
        "\r\n";

    // 1. 匹配请求行
    {
        regex request_line(R"((\w+)\s+sip:([^@]+)@([^\s]+)\s+(SIP/\d+\.\d+)\r\n)");
        smatch matches;
        if (regex_search(sip_message, matches, request_line)) {
            cout << "请求方法: " << matches[1] << '\n';
            cout << "用户名: " << matches[2] << '\n';
            cout << "域名: " << matches[3] << '\n';
            cout << "SIP版本: " << matches[4] << '\n';
        }
    }

    // 2. 匹配头部字段
    {
        // 头部字段的通用模式: 字段名: 值\r\n
        regex header(R"(([^:\r\n]+):\s*([^\r\n]+)\r\n)");
        
        sregex_iterator it(sip_message.begin(), sip_message.end(), header);
        sregex_iterator end;

        cout << "\n头部字段:\n";
        while (it != end) {
            cout << "字段: " << (*it)[1] << '\n';
            cout << "值: " << (*it)[2] << '\n';
            cout << "-------------------\n";
            ++it;
        }
    }

    // 3. 提取特定头部字段值（例如 From 字段中的标签）
    {
        regex from_pattern(R"(From:\s*[^;]+;tag=(\d+))");
        smatch matches;
        if (regex_search(sip_message, matches, from_pattern)) {
            cout << "\nFrom标签值: " << matches[1] << '\n';
        }
    }

    // 4. 分离消息头和消息体
    {
        regex body_separator(R"(\r\n\r\n(.*))");
        smatch matches;
        if (regex_search(sip_message, matches, body_separator)) {
            cout << "\n消息体长度: " << matches[1].length() << " 字节\n";
        }
    }
}

int main() {
    parse_sip_message();
    return 0;
}