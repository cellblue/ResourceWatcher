#pragma once

#include "watcher.h"
#include <map>
#include <unordered_map>

namespace resource_watcher{
class MemoryWatcher:public Watcher{
public:
    MemoryWatcher() = default;
    virtual void dataCollection() override;

private:
    std::unordered_map<std::string, std::int64_t> mem_info_; // KB
    void readMemInfo();
    int64_t getPhyTotal();
    int64_t getPhyUsed();
    int64_t getPhyFree();
    int64_t getPhyShared();
    int64_t getPhyBufferAndCached();
    int64_t getSwapTotal();
    int64_t getSwapUsed();
    int64_t getSwapFree();

};
} // namespace resource_watcher