#pragma once
#include <functional>
#include <thread>
#include <vector>
#include <future>
#include <any>
#include <variant>

#include "safe_queue.hpp"


class ThreadPool {
public:
    ThreadPool(size_t num_threads) : threads_(num_threads) {
        for (auto& thread : threads_) {
            thread = std::thread([this] { worker(); });
        }
    }

    ~ThreadPool() {
        stop_.store(true);

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
        task_queue_.push([task]() { (*task)(); });
        task_queue_.cond_.notify_one();
        return res;
    }
private:
    SafeQueue<std::function<void()>> task_queue_;
    std::vector<std::thread> threads_;
    std::atomic<bool> stop_{false};
    void worker() {
        while (!stop_.load()) {
            auto task = task_queue_.pop();
            if (task) {
                task();
            }
        }
    }
};

