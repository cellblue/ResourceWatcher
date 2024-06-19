#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>

template<typename T>
class SafeQueue {
public:
    SafeQueue() {}

    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cond_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            cond_.wait(lock);
        }
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;
};

// int main(){
//     SafeQueue<int> safe_queue;
//     safe_queue.push(11);
//     auto x = safe_queue.pop();
//     std::cout << x << std::endl;
// }