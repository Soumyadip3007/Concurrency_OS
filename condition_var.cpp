#include<iostream>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

class WiFi
{
private:
    int m_state{0};  // 0 => Connect's turn, 1 => Disconnect's turn
    int n;
    mutex mtx;                    // To synchronize the threads
    condition_variable cv;         // Condition variable for signaling

public:
    WiFi(int _n) {
        this->n = _n;
    }

    void connect(function<void()> mylambda1)
    {
        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() { return m_state == 0; });  // Wait until m_state == 0
            mylambda1();    // Execute the lambda
            m_state = 1;    // Change state
            cv.notify_all(); // Wake up other thread
        }
    }

    void disconnect(function<void()> mylambda2)
    {
        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() { return m_state == 1; });  // Wait until m_state == 1
            mylambda2();    // Execute the lambda
            m_state = 0;    // Change state
            cv.notify_all(); // Wake up other thread
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