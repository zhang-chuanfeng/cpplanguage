#include <future>
#include <chrono>
#include <random>
#include <thread>
#include <iostream>

using namespace std;

int doSomething(char c)
{
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10, 1000);

    for (int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}

int func1()
{
    return doSomething('.');
}

int func2()
{
    return doSomething('+');
}

int main()
{
    cout << "starting func1() in background"
         << " and func2() in foreground:" << endl;

    future<int> result1(async(launch::async,func1));

    int result2 = func2();

    int result = result1.get() + result2;
    cout << "\nresult of func1()+func2(): " << result << endl;
}
