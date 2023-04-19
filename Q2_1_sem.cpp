//Q2_1_sem.cpp

#include <iostream>
#include <thread>
#include <semaphore.h>

sem_t semaphore;

void runMeFirst() {
    std::cout << "Run me first" << std::endl;
    sem_post(&semaphore);
}

void runMeSecond() {
    sem_wait(&semaphore);
    std::cout << "I run second" << std::endl;
}

int main() {
    sem_init(&semaphore, 0, 0);
    std::thread t1(runMeFirst);
    std::thread t2(runMeSecond);
    t1.join();
    t2.join();
    sem_destroy(&semaphore);
    return 0;
}

