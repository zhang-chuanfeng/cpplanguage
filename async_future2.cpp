#include <random>
#include <chrono>
#include <thread>
#include <iostream>
#include <future>

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

int main()
{
#if defined _GLIBCXX_HAS_GTHREADS && defined _GLIBCXX_USE_SCHED_YIELD
    cout << "defined _GLIBCXX_HAS_GTHREADS && defined _GLIBCXX_USE_SCHED_YIELD" << endl;
#endif

    cout << "starting 2 operations asynchronously" << endl;

    auto f1 = async([]{ doSomething('.'); });
    auto f2 = async([]{ doSomething('+'); });

    // if at one of the background tasks is running
    if (f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
        f2.wait_for(chrono::seconds(0)) != future_status::deferred)
    {
        // poll until at least one of the loops finished
        while (f1.wait_for(chrono::seconds(0)) != future_status::ready &&
               f2.wait_for(chrono::seconds(0)) != future_status::ready)
        {
            this_thread::yield();
        }
    }

    cout.put('\n').flush();

    try {
        f1.get();
        f2.get();
    } catch (const exception& e) {
        cout << "\nEXCEPTION: " << e.what() << endl;
    }
    cout << "\ndone" << endl;
}