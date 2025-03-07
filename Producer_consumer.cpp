#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

const int BUFFER_SIZE = 5;
queue<int>buffer;
mutex mtx;
condition_variable cv_p;
condition_variable cv_c;

//Producer function
void producer(int id)
{
    for(int i=0;i<10;i++)
    {
        unique_lock<mutex> lck(mtx);
        cv_p.wait(lck, []{return buffer.size()<BUFFER_SIZE;});
        buffer.push(i);
        cout<<"Producer "<<id<<" produced "<<i<<endl;
        cv_c.notify_one();  //notify consumer that buffer is not empty
        this_thread::sleep_for(chrono::milliseconds(500)); //sleep for 500ms
    }
}

//Consumer function
void consumer(int id)
{
    for(int i=0;i<10;i++)
    {
        unique_lock<mutex>lck(mtx);
        cv_c.wait(lck, []{return buffer.size()>0;});
        int item = buffer.front();
        buffer.pop();
        cout<<"Consumer "<<id<<" consumed "<<item<<endl;
        cv_p.notify_one();  //notify producer that buffer is not full
        this_thread::sleep_for(chrono::milliseconds(500)); //sleep for 500ms
    }
}

int main()
{
    thread t1(producer, 0);
    thread t2(consumer, 0);
    thread t3(producer, 1);
    thread t4(consumer, 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}