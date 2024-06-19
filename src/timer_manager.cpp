#include "timer_manager.h"
namespace resource_watcher{
void TimerManager::addTimer(std::string name, std::chrono::milliseconds delay, std::function<void()> callback){
        int timerFd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
        if (timerFd == -1) {
            perror("timerfd_create");
            exit(EXIT_FAILURE);
        }

        itimerspec its;
        its.it_value = {delay.count() / 1000, (delay.count() % 1000) * 1000000L};
        its.it_interval = {delay.count() / 1000, (delay.count() % 1000) * 1000000L};
        if (timerfd_settime(timerFd, 0, &its, nullptr) == -1) {
            perror("timerfd_settime");
            exit(EXIT_FAILURE);
        }

        epoll_event ev;
        ev.events = EPOLLIN ;
        ev.data.fd = timerFd;
        if (epoll_ctl(epollFd, EPOLL_CTL_ADD, timerFd, &ev) == -1) {
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
        }

        timers[timerFd] = {name, delay, std::move(callback)};
}

void TimerManager::run(){
     while (true) {
        epoll_event events[maxEvents];
        int nfds = epoll_wait(epollFd, events, maxEvents, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < nfds; ++i) {
            auto& [timer_id, timer_delay, timer_callback] = timers[events[i].data.fd];
            timer_callback();
        }
    }       
}
} // namespace resource_watcher