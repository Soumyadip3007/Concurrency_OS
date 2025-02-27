Thread Synchronization Patterns 🚦


This repository contains multithreading problems where different thread synchronization patterns are implemented using C++ concurrency primitives.

🔥 What's Inside?
Pattern	Description	Techniques Used
Zero-Even-Odd	--> Print numbers in 01020304... format with three threads	--> mutex, condition_variable
WiFi Connect-Disconnect	-->Synchronize two threads to print "Connected->Disconnected->"	--> Spinlock, condition_variable, atomic
Upcoming	More thread synchronization problems...	Stay tuned 🚀

1. Zero-Even-Odd
Problem Statement:
Given three threads:

One thread prints Zero.
One thread prints Even numbers.
One thread prints Odd numbers.
Threads should print numbers in this order:

0102030405...
✅ Techniques Used:
mutex
condition_variable
Proper Turn Synchronization

2. WiFi Connect-Disconnect
Problem Statement:
Two threads should print:
Connected->Disconnected->Connected->Disconnected->
for N times without any race condition or infinite loops.

Implementations:
1)Spinlock + Atomic	Busy-waiting 🔥	✅ || (Working but inefficient)
2)Condition Variable	Optimal	✅|| (Zero CPU wastage)
3)Binary Semaphore (C++20)	|| Fastest & Cleanest	🔄 Coming Soon...

🔧 How to Run
Prerequisites:
C++17 or above
g++ or any modern compiler supporting threads
Build & Run

bash-->
g++ main.cpp -std=c++17 -pthread -o thread_patterns
./thread_patterns

🔍 What's Next?
Producer-Consumer using semaphore
Reader-Writer Locks
Dining Philosophers Problem
Barrier Synchronization

🎯 Contributing:
If you have any new thread synchronization pattern ideas, feel free to fork this repo and create a pull request!

📌 Author
Soumyadip Kar
Masters Student @ IIT Kharagpur
Loves Multithreading, Concurrency, and System Programming ❤️
