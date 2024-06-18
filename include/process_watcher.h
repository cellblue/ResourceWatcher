#pragma once

#include "watcher.h"
#include <vector>
#include <unordered_map>
namespace resource_watcher{
class ProcessWatcher:public Watcher{
public:
    ProcessWatcher() = default;
    virtual void dataCollection();
private:
    void readProcDir();
    char readProcState(std::string pid);
    int32_t getTotal();
    int32_t getRuning();
    int32_t getSleeping();
    int32_t getStopped();
    int32_t getZombie();
    std::vector<int32_t> pids_;
    std::unordered_map<char, int32_t> state_counter_;
};
} // namespace resource_watcher