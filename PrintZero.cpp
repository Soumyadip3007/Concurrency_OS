#include<iostream>
#include<functional>
#include<thread>
#include<atomic>

using namespace std;
class ZeroEvenOdd {
    private:
        int n;
        std::atomic<int>m_PrintZeroState{PRINT_ZERO_BEFORE_ODD};
        enum PrintZeroState{
            PRINT_ZERO_BEFORE_ODD,
            PRINTED_ZERO_BEFORE_ODD,
            PRINT_ZERO_BEFORE_EVEN,
            PRINTED_ZERO_BEFORE_EVEN,
        };
        int currNum{1}; //can be taken as atomic
    public:
        ZeroEvenOdd(int n) { //constructor
            this->n = n;
        }
    
        // printNumber(x) outputs "x", where x is an integer.
        void zero(function<void(int)> printNumber) {
            while(currNum<=n)
            {
                auto state=m_PrintZeroState.load();
                if(state!=PRINT_ZERO_BEFORE_ODD&&state!=PRINT_ZERO_BEFORE_EVEN)
                {
                    continue;
                }
                if(currNum>n) break;
                printNumber(0);
                auto newState=(state==PRINT_ZERO_BEFORE_ODD)?PRINTED_ZERO_BEFORE_ODD:PRINTED_ZERO_BEFORE_EVEN;
                m_PrintZeroState=newState;
            }
        }
    
        void even(function<void(int)> printNumber) {
            while(currNum<=n)
            {
                if(m_PrintZeroState!=PRINTED_ZERO_BEFORE_EVEN)
                {
                    continue;
                }
                if(currNum>n) break;
                printNumber(currNum++);
                m_PrintZeroState=PRINT_ZERO_BEFORE_ODD;
            }
        }
    
        void odd(function<void(int)> printNumber) {
            while(currNum<=n)
            {
                if(m_PrintZeroState!=PRINTED_ZERO_BEFORE_ODD)
                {
                    continue;
                }
                if(currNum>n) break;
                printNumber(currNum++);
                m_PrintZeroState=PRINT_ZERO_BEFORE_EVEN;
            }
        }
    };

void test() {
    int n = 5;
    ZeroEvenOdd obj(n);

    auto printNumber = [](int x) { cout << x << " "; };

    thread t1(&ZeroEvenOdd::zero, &obj, printNumber);
    thread t2(&ZeroEvenOdd::odd, &obj, printNumber);
    thread t3(&ZeroEvenOdd::even, &obj, printNumber);

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    test();
    return 0;
}