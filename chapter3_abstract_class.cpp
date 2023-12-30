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

template <typename T>
class Container
{
public:
    virtual T &operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container(){};
};

template <typename T>
void use(Container<T> &c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << c[i] << "\n";
}

// 含有纯虚函数的类为抽象类
template <typename T>
class Vector_container : public Container<T>
{
    std::vector<T> v;

public:
    Vector_container(int s) : v(s) {}
    Vector_container(std::initializer_list<T> il) : v(il) {}
    ~Vector_container() {}

    double &operator[](int i) override { return v[i]; }
    int size() const override { return v.size(); }
};

template <typename T>
class List_container : public Container<T>
{
    std::list<T> v;

public:
    List_container() {}
    List_container(std::initializer_list<T> il) : v(il) {}
    ~List_container() {}

    double &operator[](int i) override
    {
        for (auto &x : v)
        {
            if (i == 0)
                return x;
            --i;
        }
        throw std::out_of_range("List container");
    }
    int size() const override { return v.size(); }
};

int main()
try
{
    Vector_container<double> vc{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    use(vc);
    List_container<double> lc{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
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

// 3.抽象机制

// 类
//  具体类型
//      1.complex一种算术类型 2.容器
//  抽象类型
//      1.Container
//        class Container
//        {
//        public:
//            virtual T &operator[](int) = 0;
//            virtual int size() const = 0;
//            virtual ~Container(){};
//        };
//  虚函数
//      vtbl
//  类层次
//      继承、基类 子类
//          1.接口继承  2.实现继承
//  拷贝和移动
//      1.拷贝构造 2.拷贝运算符
//      1.移动构造 2.移动运算符
//      && "右值引用"  std::move
//  资源管理
//      通过定义构造函数、拷贝、移动操作和析构函数  对受控资源声明周期管理
//      移动构造   作用域移动
//      资源句柄
//          1.存放内存vector
//          2.存放系统线程的thread
//          3.存放文件句柄的fstream
//          4.unique_ptr  智能指针  本身就是资源句柄
//
//          std::vector<thread> my_threads;
//          std::vector init(int n) {
//              std::thread t {heartbeat}
//              my_threads.push_back(std::move(t)); // 把t移动到my_threads
//              //...
//              std::vector vec(n);
//              for (int i=0; i<vec.size(); ++i) vec[i] = 777;
//              return vec;  // 移动vec到init()之外
//          }
//  抑制操作
//      1.没有移动 没有拷贝   使用delete   显式声明析构函数 移动操作不会隐式生成
//      2.抽象类的基类  删除默认拷贝和移动操作
//  模板
//      1.参数化模板    template<typename T>
//      2.函数模板
//      3. 函数对象
//          template <typename T>
//          class Less_than
//          {
//              const T val;
//          public:
//              Less_than(const T &v) : val(v) {}
//              bool operator()(const T &x) const {return x < val};
//          };
//      容器和操作进行分离      操作是函数对象
//      template<typename C, typename P>
//      int count(const C& c, P pred)
//
//      template<typename C, typename Opr>
//      void for_all(C& c, Opr op)
//
//      lambda表达式    隐式生成函数对象 []()->{}
//      [&] [=]
//      4.可变参数模板
//          template<typename T, typename... Tail>
//          void f(T head, Tail... tail)
//      5.别名
//          using
//          template<typename C>
//          using Element_type = typename C::value_type