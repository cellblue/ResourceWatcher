#pragma once
#include <functional>
#include <thread>
#include <vector>

#include "safe_queue.hpp"

template<typename T>
class ThreadPool {
private:
    SafeQueue<T> task_queue_;
    std::vector<std::thread> threads_;
    bool stop_ = false;

    void worker() {
        while (!stop_) {
            T task = task_queue_.pop();
            if (task != nullptr) {
                task();
            }
        }
    }

public:
    ThreadPool(size_t num_threads) : threads_(num_threads) {
        for (auto& thread : threads_) {
            thread = std::thread([this] { worker(); });
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(task_queue_.mutex_);
            stop_ = true;
        }
        task_queue_.cond_.notify_all();

        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    template<typename Func, typename... Args>
    auto enqueue(Func&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using return_type = decltype(f(args...));

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            std::lock_guard<std::mutex> lock(task_queue_.mutex_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            task_queue_.queue_.push([=]() { (*task)(); });
        }
        task_queue_.cond_.notify_one();
        return res;
    }
};


