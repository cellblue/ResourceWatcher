#include "memory_watcher.h"
#include "common.h"

#include <fstream>
#include <filesystem>

namespace resource_watcher{

int64_t MemoryWatcher::getPhyTotal(){
    return mem_info_["MemTotal"];
}

int64_t MemoryWatcher::getPhyUsed(){
    return mem_info_["MemTotal"] - mem_info_["MemFree"] - mem_info_["Buffers"] - mem_info_["Cached"];
}

int64_t MemoryWatcher::getPhyFree(){
    return mem_info_["MemFree"];
}

int64_t MemoryWatcher::getPhyShared(){
    return mem_info_["Shmem"];
}

int64_t MemoryWatcher::getPhyBufferAndCached(){
    return mem_info_["Buffers"] + mem_info_["Cached"];
}

int64_t MemoryWatcher::getSwapTotal(){
    return mem_info_["SwapTotal"];
}

int64_t MemoryWatcher::getSwapUsed(){
    return mem_info_["SwapTotal"] - mem_info_["SwapFree"];
}

int64_t MemoryWatcher::getSwapFree(){
    return mem_info_["SwapFree"];
}

void MemoryWatcher::readMemInfo(){
    std::ifstream file(mem_info.data());
    std::string line;
    while(std::getline(file, line)){
         size_t colon_pos = line.find(':');
         if(colon_pos != std::string::npos){
            std::istringstream iss(line);
            std::string key;
            int64_t value;
            iss >> key >> value;
            key.erase(key.find(':'), 1);
            mem_info_[key] = value;
         }
    }
}

void MemoryWatcher::dataCollection(){
    // auto now = std::chrono::system_clock::now();
    // auto timestamp = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    // auto millis = timestamp.time_since_epoch().count();
    // std::cout << "Current time in milliseconds since epoch: " << millis << std::endl;
    readMemInfo();
    
    auto phy_mem = Watcher::sys_data_->mutable_phy_mem();
    phy_mem->set_name("phy_mem");
    phy_mem->set_total(getPhyTotal());
    phy_mem->set_used(getPhyUsed());
    phy_mem->set_free(getPhyFree());
    phy_mem->set_shared(getPhyShared());
    phy_mem->set_buffer_and_cached(getPhyBufferAndCached());
    // std::cout << phy_mem->DebugString() << std::endl;

    auto swap_mem = Watcher::sys_data_->mutable_swap_mem();
    swap_mem->set_name("swap_mem");
    swap_mem->set_total(getSwapTotal());
    swap_mem->set_used(getSwapUsed());
    swap_mem->set_free(getSwapFree());
    // std::cout << swap_mem->DebugString() << std::endl;
}
} // namespace resource_watcher