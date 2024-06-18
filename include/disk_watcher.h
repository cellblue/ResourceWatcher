#pragma once

#include "watcher.h"

#include <vector>
#include <filesystem>

namespace resource_watcher{
namespace fs = std::filesystem;

struct DiskInfo {
    std::string_view name;
    std::string_view mount_point;
    fs::file_size_type capacity;
    fs::file_size_type available;
    fs::file_size_type free;

    DiskInfo(std::string_view name, std::string_view mount_point, 
             fs::file_size_type capacity, fs::file_size_type available, 
             fs::file_size_type free)
            : name(name), mount_point(mount_point),
                capacity(capacity), available(available), free(free) {}
};


class DiskWatcher:public Watcher{
public:
    DiskWatcher();
    virtual void dataCollection();
private:
    std::vector<DiskInfo> disk_info_;
    void getDiskInfo();
};
} // namespace resource_watcher