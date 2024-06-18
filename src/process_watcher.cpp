#include "process_watcher.h"
#include "common.h"
#include "process_watcher.h"
#include <fstream>
#include <filesystem>

namespace resource_watcher{
// using fs = std::filesystem;

char ProcessWatcher::readProcState (std::string pid){
    std::string path = std::string(proc) + "/" + pid + "/stat";
    std::ifstream file(path);
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    std::string tmp ;
    char state;
    iss >> tmp >> tmp >> state;
    return state;
}

void ProcessWatcher::readProcDir(){
    pids_.clear();
    state_counter_.clear();
    for(auto& p : std::filesystem::directory_iterator(proc.data())){
        if (p.is_directory()){
            auto pid_str = p.path().filename().string();
            try {
                int32_t pid = std::stoi(pid_str);
                pids_.emplace_back(pid);
                auto state = readProcState(pid_str);
                state_counter_[state]++;
            } catch (const std::invalid_argument& ia) {
                continue;
            } 
        }
    }
}

int32_t ProcessWatcher::getTotal(){
    return pids_.size();
}

int32_t ProcessWatcher::getRuning(){
    return state_counter_['R'];
}

int32_t ProcessWatcher::getSleeping(){
    return state_counter_['S'] + state_counter_['W'] 
        + state_counter_['C'] + state_counter_['P']
        + state_counter_['I'];
}

int32_t ProcessWatcher::getStopped(){
    return state_counter_['T'];
}

int32_t ProcessWatcher::getZombie(){
    return state_counter_['Z'] + state_counter_['X'];
}

void ProcessWatcher::dataCollection(){
    readProcDir();
    auto tasks = Watcher::sys_data_->mutable_tasks();
    tasks->set_name("sys_tasks");
    tasks->set_total(getTotal());
    tasks->set_running(getRuning());
    tasks->set_sleeping(getSleeping());
    tasks->set_stopped(getStopped());
    tasks->set_zombie(getZombie());
    std::cout << tasks->DebugString() << std::endl;
}
} // namespace resource_watcher