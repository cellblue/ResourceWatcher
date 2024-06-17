#include "app.h"

namespace resource_watcher{

App::App() : timer_manager_(std::make_unique<TimerManager>(512)){
    sys_watchers_["cpu"] = std::make_unique<CPUWatcher>();
    sys_watchers_["mem"] = std::make_unique<MemoryWatcher>();
    // sys_watchers_["disks"] = std::make_unique<DiskWatcher>();
    // sys_watchers_["tasks"] = std::make_unique<ProcessWatcher>();
}

App::~App() {

}

void App::start() {
    for(const auto &[reasource, watcher] : sys_watchers_){
        timer_manager_->addTimer(reasource,std::chrono::milliseconds(500),[&watcher](){
            watcher->dataCollection();
        });
    }
    timer_manager_->run();
}

void App::stop() {
    
}

} // namespace resource_watcher