#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

class TimeZoneConverter {
public:
    static std::string getPosixTZ() {
        time_t now = time(nullptr);
        struct tm local_tm = *localtime(&now);
        
        // 获取时区缩写和偏移
        // tzname 是全局变量，包含标准时间和夏令时的缩写
        const char* std_zone = tzname[0];  // 标准时区缩写
        const char* dst_zone = tzname[1];  // 夏令时缩写
        
        // 计算时区偏移（秒）
        long offset = -timezone;  // timezone 是全局变量，表示UTC偏移秒数
        int hours = offset / 3600;
        int mins = (std::abs(offset) % 3600) / 60;
        
        std::ostringstream oss;
        oss << std_zone;  // 时区缩写
        
        // 添加偏移
        oss << (hours >= 0 ? "-" : "") << std::abs(hours);
        
        if (mins != 0) {
            oss << ":" << mins;
        }
        
        // 如果有夏令时规则，添加夏令时信息
        if (local_tm.tm_isdst > 0 && dst_zone[0] != '\0') {
            oss << dst_zone;
        }
        
        return oss.str();
    }
    
    static void showSystemTZInfo() {
        // 确保初始化时区信息
        tzset();
        
        std::cout << "标准时区缩写: " << tzname[0] << "\n";
        std::cout << "夏令时缩写: " << tzname[1] << "\n";
        std::cout << "UTC偏移(秒): " << timezone << "\n";
        std::cout << "POSIX格式时区: " << getPosixTZ() << "\n";
    }
};

int main() {
    // 设置本地环境
    setenv("TZ", "Asia/Shanghai", 1);
    tzset();
    
    TimeZoneConverter::showSystemTZInfo();
    
    // 测试不同时区
    std::cout << "\n切换到其他时区：\n";
    setenv("TZ", "America/New_York", 1);
    tzset();
    
    TimeZoneConverter::showSystemTZInfo();
    
    return 0;
}