#include <vector>
#include <memory>
#include "watcher.h"
#include "cpu_watcher.h"
#include "disk_watcher.h"
#include "memory_watcher.h"
#include "process_watcher.h"

#include "timer_manager.h"

namespace resource_watcher {

class App{
private:
    std::vector<std::unique_ptr<Watcher> > sys_watchers_;
    std::unique_ptr<TimerManager> timer_manager_;
public:
    App(); 
    ~App(); 
    void start();
    void stop();
};

};