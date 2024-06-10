#include <iostream>
#include <map>
#include <memory>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <chrono>
#include <thread>
#include <functional>

namespace resource_watcher{
class TimerManager {
public:
    TimerManager(int maxEvents) : epollFd(epoll_create1(0)), maxEvents(maxEvents) {
        if (epollFd == -1) {
            perror("epoll_create1");
            exit(EXIT_FAILURE);
        }
    }

    ~TimerManager() {
        close(epollFd);
    }

    void addTimer(std::string name, std::chrono::milliseconds delay, std::function<void()> callback);

    void run();

private:
    int epollFd;
    int maxEvents;
    std::map<int, std::pair<std::string, std::function<void()>>> timers;
};

};