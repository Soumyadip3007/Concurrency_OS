//Thread Synchronization using spinlock
//Spinlock is a busy waiting technique where a thread waits in a loop repeatedly checking until a condition is satisfied.
#include<iostream>
#include<functional>
#include<thread>
#include<atomic>
using namespace std;

class WiFi
{
private:
    atomic<int> m_state{0};
    int n;
public:
    WiFi(int _n) {
        this->n = _n;
    }

    void connect(function<void()> mylambda1)
    {
        for (int i = 0; i < n; i++)
        {
            spinlock(0);  // Wait until state is 0
            mylambda1();  // Execute lambda
            m_state.store(1); // Change state to 1
        }
    }

    void disconnect(function<void()> mylambda2)
    {
        for (int i = 0; i < n; i++)
        {
            spinlock(1);  // Wait until state is 1
            mylambda2();  // Execute lambda
            m_state.store(0); // Change state to 0
        }
    }

    void spinlock(int state)
    {
        while (m_state.load() != state)
        {
            this_thread::yield(); // Give other thread a chance to run
        }
    }
};

void test() {
    int n = 5;
    WiFi obj(n);
    string s1 = "Connected";
    string s2 = "Disconnected";

    auto mylambda1 = [&s1]() { cout << s1 << "->"; };
    auto mylambda2 = [&s2]() { cout << s2 << "->"; };

    thread t1(&WiFi::connect, &obj, mylambda1);
    thread t2(&WiFi::disconnect, &obj, mylambda2);

    t1.join();
    t2.join();

    cout << "Done!" << endl;
}

int main()
{
    test();
    return 0;
}
