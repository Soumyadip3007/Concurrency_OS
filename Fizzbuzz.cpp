#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

class FizzBuzz {
private:
    int n;
    int i;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->i = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 == 0 && i % 5 != 0) || i > n; });
            if (i > n) break;
            printFizz();
            i++;
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 5 == 0 && i % 3 != 0) || i > n; });
            if (i > n) break;
            printBuzz();
            i++;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 15 == 0) || i > n; });
            if (i > n) break;
            printFizzBuzz();
            i++;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return (i % 3 != 0 && i % 5 != 0) || i > n; });
            if (i > n) break;
            printNumber(i);
            i++;
            cv.notify_all();
        }
    }
};

int main() {
    int n=15;
    FizzBuzz fb(n);  // Print numbers from 1 to 15

    // Lambda functions for printing
    auto printFizz = []() { std::cout << "fizz, "; };
    auto printBuzz = []() { std::cout << "buzz, "; };
    auto printFizzBuzz = [n]() { n == 15 ? std::cout << "fizzbuzz " : std::cout << "fizzbuzz, "; };
    auto printNumber = [](int x) { std::cout << x << ", "; };

    // Create and start threads
    std::thread threadA([&]() { fb.fizz(printFizz); });
    std::thread threadB([&]() { fb.buzz(printBuzz); });
    std::thread threadC([&]() { fb.fizzbuzz(printFizzBuzz); });
    std::thread threadD([&]() { fb.number(printNumber); });

    // Wait for all threads to finish
    threadA.join();
    threadB.join();
    threadC.join();
    threadD.join();

    return 0;
}