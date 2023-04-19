#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

sem_t sem_first, sem_second;

void runMeFirst() {
    sem_wait(&sem_first);
    cout << "I run second" << endl;
    sem_post(&sem_second);
}

void runMeSecond() {
    sem_wait(&sem_second);
    cout << "I run third" << endl;
}

void runMeThird() {
    cout << "Run me first" << endl;
}

int main() {
    // Initialize semaphores
    sem_init(&sem_first, 0, 1);
    sem_init(&sem_second, 0, 0);

    // Create threads
    thread t2(runMeFirst);
    thread t3(runMeSecond);
    thread t1(runMeThird);

    // Join threads
    t3.join();
    t1.join();
    t2.join();

    // Destroy semaphores
    sem_destroy(&sem_first);
    sem_destroy(&sem_second);


    return 0;
}



