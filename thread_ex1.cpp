#include <iostream>
#include <thread>
using namespace std;

bool stop = true;

void thread1() { 
    cout << "I am thread 1\n"; 
    stop=false; 
}

void thread2() { 
    while (stop); 
    cout << "I am thread2\n"; 
}

int main() {
thread t1(thread1);
thread t2(thread2);
t1.join();
t2.join();
return 0;
}



