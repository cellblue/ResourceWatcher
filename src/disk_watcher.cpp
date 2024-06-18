#include "disk_watcher.h"
#include "common.h"
#include <fstream>

namespace resource_watcher{
void DiskWatcher::getDiskInfo(){
    std::ifstream mountsFile(mounts.data());
    std::string line;
    disk_infos_.clear();

    while (std::getline(mountsFile, line)) {
        std::istringstream iss(line);
        std::string filesystem, mount_point, type, options, dump, pass;

        if (iss >> filesystem >> mount_point >> type >> options >> dump >> pass) {
            try{
                auto space_res = fs::space(mount_point);
                disk_infos_.emplace_back(filesystem, mount_point, space_res.capacity, space_res.available, space_res.free);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

}

void DiskWatcher::dataCollection(){
    getDiskInfo();
    for(const auto & disk_info : disk_infos_){
        Disk* disk_pb = Watcher::sys_data_->add_disks();   
        disk_pb->set_file_system(disk_info.name);
        disk_pb->set_capacity(disk_info.capacity);
        disk_pb->set_available(disk_info.available);
        disk_pb->set_free(disk_info.free);
        disk_pb->set_mount_point(disk_info.mount_point.data());
        std::cout << disk_pb->DebugString() << std::endl;
    }
}

} // namespace resource_watcher