#pragma once

#include "watcher.h"

#include <vector>
#include <filesystem>

namespace resource_watcher{
namespace fs = std::filesystem;

struct DiskInfo {
    std::string name;
    std::string mount_point;
    int64_t capacity;
    int64_t available;
    int64_t free;

    DiskInfo(std::string name, std::string mount_point, 
             int64_t capacity, int64_t available, 
             int64_t free)
            : name(name), mount_point(mount_point),
                capacity(capacity), available(available), free(free) {}
};


class DiskWatcher:public Watcher{
public:
    DiskWatcher() = default;
    virtual void dataCollection();
private:
    std::vector<DiskInfo> disk_infos_;
    void getDiskInfo();
};
} // namespace resource_watcher