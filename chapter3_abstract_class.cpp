// 抽象机制

// 类

// 1. 具体类型
// complex
// vector

// 2. 抽象类型
// 使用者与类的实现细节完全隔离开来
// 分离接口与表现形式并且放弃了局部变量

#include <iostream>
#include <vector>
#include <list>
#include <initializer_list>

template<typename T>
class Container
{
public:
    virtual T &operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container(){};
};

template<typename T>
void use(Container<T> &c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << c[i] << "\n";
}

// 含有纯虚函数的类为抽象类
template<typename T>
class Vector_container: public Container<T> {
    std::vector<T> v;
public:
    Vector_container(int s): v(s) {}
    Vector_container(std::initializer_list<T> il): v(il) {}
    ~Vector_container() {}

    double &operator[](int i) override {return v[i];}
    int size() const override {return v.size();}
};

template<typename T>
class List_container: public Container<T> {
    std::list<T> v;
public:
    List_container() {}
    List_container(std::initializer_list<T> il): v(il) {}
    ~List_container() {}

    double &operator[](int i) override {
        for (auto& x: v) {
            if (i==0) return x;
            --i;
        }
        throw std::out_of_range("List container");
    }
    int size() const override {return v.size();}
};

int main()
try
{
    Vector_container<double> vc {10, 9, 8,7,6,5,4,3,2,1,0};
    use(vc);
    List_container<double> lc {10, 9, 8,7,6,5,4,3,2,1,0};
    use(lc);
    return 0;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    return 2;
}

