/* 
    Concurrent Queue:
	Build a queue data structure (with a capacity c) such that it can support concurrent 
    calls for push and pop. The queue has only push and pop methods. Both are blocking 
    calls. If the queue is empty, and ‘pop’ is called, it should wait for an element to
    be added to the queue and pop the element. If the queue is full and a ‘push’ is 
    called, wait for a space to be created and pop the element.
*/

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <vector>

template <typename T>
class ConcurrentQueue{
public:
    ConcurrentQueue(int capacity) : capactiy_(capacity) {}

    void push(T val){
        // Acquire lock on mutex.
        std::unique_lock locker(mtx_);

        // Wait till the queue size is less than capacity.
        cv_.wait(locker, [&](){return this->q_.size() < capactiy_;});

        // Push val into queue.
        q_.push(val);
        std::cout << "pushed " << val << std::endl;

        // Unlock mutex.
        locker.unlock();

        // Notify others who are waiting on the the conditional variable cv_.
        cv_.notify_one();
    }

    T pop(){
        // Acquire lock on mutex.
        std::unique_lock locker(mtx_);

        // Wait till the queue size is non empty.
        cv_.wait(locker, [&](){return !this->q_.empty();});

        // Pop val from queue.
        T val = q_.front();
        q_.pop();
        std::cout << "popped " << val << std::endl;

        // Unlock mutex.
        locker.unlock();

        // Notify others who are waiting on the the conditional variable cv_.
        cv_.notify_one();

        return val;
    }


private:
    std::mutex mtx_;
    std::condition_variable cv_;
    int capactiy_;
    std::queue<T> q_;
};

std::mutex log_mtx;
void function(ConcurrentQueue<int> &cq,int id){
    int x = rand() % 10;
    // Randomly push into queue and pop from queue with 0.5 probability each.
    if(x < 5){
        std::unique_lock locker(log_mtx);
        std::cout << "thread " << id << ": pushing " << x << std::endl; 
        locker.unlock();
        cq.push(x);
    }else{
        std::unique_lock locker(log_mtx);
        std::cout << "thread " << id << ": popping " << std::endl;
        locker.unlock();
        int val = cq.pop();
    }
}

int main(){
    srand (time(NULL));
    ConcurrentQueue<int> cq(5);
    std::vector<std::thread> threads(10);

    // Spawn threads to perform push and pop into queue.
    for(int i=0;i<10;i++){
        threads[i] = std::thread(function,std::ref(cq),i);
    }

    // Join all the spawned threads.
    for(int i=0;i<10;i++){
        threads[i].join();
    }
}