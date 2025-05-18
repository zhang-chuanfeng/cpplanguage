#include <iostream>
#include <system_error>
#include <string>

// 定义自定义错误码
enum class CustomError {
    Success = 0,
    InvalidInput = 1,
    DatabaseError = 2,
    NetworkError = 3
};

// 自定义错误类别
class CustomErrorCategory : public std::error_category {
public:
    // 获取错误类别名称
    const char* name() const noexcept override {
        return "CustomError";
    }
    
    // 获取错误消息
    std::string message(int ev) const override {
        switch(static_cast<CustomError>(ev)) {
            case CustomError::Success:
                return "操作成功";
            case CustomError::InvalidInput:
                return "无效的输入";
            case CustomError::DatabaseError:
                return "数据库错误";
            case CustomError::NetworkError:
                return "网络连接错误";
            default:
                return "未知错误";
        }
    }

    // 单例模式
    static const CustomErrorCategory& instance() {
        static CustomErrorCategory instance;
        return instance;
    }
};

// 为自定义错误类型创建 error_code
std::error_code make_error_code(CustomError e) {
    return {static_cast<int>(e), CustomErrorCategory::instance()};
}

// 声明自定义错误类型可以转换为 error_code
namespace std {
    template <>
    struct is_error_code_enum<CustomError> : true_type {};
}

// 模拟可能抛出错误的函数
void doSomething(int value) {
    if (value < 0) {
        throw std::system_error(CustomError::InvalidInput);
    } else if (value > 100) {
        throw std::system_error(CustomError::NetworkError);
    }
}

int main() {
    try {
        std::cout << "尝试使用无效输入..." << std::endl;
        doSomething(-1);
    } catch (const std::system_error& e) {
        std::cout << "捕获到系统错误！" << std::endl;
        std::cout << "错误码: " << e.code().value() << std::endl;
        std::cout << "错误类别: " << e.code().category().name() << std::endl;
        std::cout << "错误信息: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n尝试触发网络错误..." << std::endl;
        doSomething(101);
    } catch (const std::system_error& e) {
        std::cout << "捕获到系统错误！" << std::endl;
        std::cout << "错误码: " << e.code().value() << std::endl;
        std::cout << "错误类别: " << e.code().category().name() << std::endl;
        std::cout << "错误信息: " << e.what() << std::endl;
    }

    return 0;
}
