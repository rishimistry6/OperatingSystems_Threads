// Rishi Mistry
// DLM: 04/14/23

#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

using namespace std;

struct requestStructure {
    int request_id;
    string ip_address;
    string page_requested;
};

// Global variables
queue<requestStructure> msg_queue;    
mutex mtx;                          
condition_variable cv;               
int request_counter = 0;            // Counter for request IDs
string webPages[10] = {"ebay.com", "spotify.com", "nike.com", "pinterest.com", "tesla.com",
                      "linkedin.com", "reddit.com", "amazon.com", "apple.com", "youtube.com"}; // List of web pages

int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void listen() {
    while (true) {
        // Sleep for a random duration between 1-3 seconds
        this_thread::sleep_for(chrono::seconds(getRandomNumber(1, 3)));

        requestStructure req;
        req.request_id = ++request_counter;
        req.ip_address = "";
        req.page_requested = webPages[getRandomNumber(0, 9)];

        // Lock the mutex and add the request to the message queue
        unique_lock<mutex> lock(mtx);
        msg_queue.push(req);
        cout << "New request received: Request ID = " << req.request_id << ", Web page requested = " << req.page_requested << endl;
        lock.unlock();

        // Notify a thread to consume the request
        cv.notify_one();
    }
}

void do_request(int thread_id) {
    while (true) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [] { return !msg_queue.empty(); });

        requestStructure req = msg_queue.front();
        msg_queue.pop();

        lock.unlock();

        // Process the request
        cout << "Thread " << thread_id << " completed request " << req.request_id << " requesting webpage " << req.page_requested << endl;
    }
}

int main() {
    thread listener(listen);

    vector<thread> request_threads;
    for (int i = 1; i <= 3; i++) {
        request_threads.emplace_back(do_request, i);
    }

    listener.join();
    for (auto& t : request_threads) {
        t.join();
    }

    return 0;
}
