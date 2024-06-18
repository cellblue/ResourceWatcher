#include "disk_watcher.h"
#include <ifstream>
namespace resource_watcher{
void getDiskInfo(){
    std::ifstream mountsFile("/proc/mounts");
    std::string line;
    disk_info_.clear();

    while (std::getline(mountsFile, line)) {
        std::istringstream iss(line);
        std::string filesystem, mount_point, type, options, dump, pass;

        if (iss >> filesystem >> mount_point >> type >> options >> dump >> pass) {
            auto space_res = fs::space(filesystem);
            disk_info_.emplace_back(filesystem, mount_point, space_res.capacity, space_res.available, space_res.free);
        }
    }

}

void DiskWatcher::dataCollection(){
    getDiskInfo();
    
}

} // namespace resource_watcher