#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <chrono>
#include <thread>
#include <functional>
#include "thread_pool.hpp"

namespace resource_watcher{
class TimerManager {
public:
    TimerManager(int max_events) : epoll_fd_(epoll_create1(0)), max_events_(max_events) {
        
        if (epoll_fd_ == -1) {
            perror("epoll_create1");
            exit(EXIT_FAILURE);
        }
    }

    ~TimerManager() {
        close(epoll_fd_);
    }

    void addTimer(std::string name, std::chrono::milliseconds delay, std::function<void()> callback);

    void run();

private:
    int epoll_fd_;
    int max_events_;
    std::map<int, std::tuple<std::string, std::chrono::milliseconds, std::function<void()>>> timers;
    ThreadPool thread_pool_;
};

} // namespace resource_watcher