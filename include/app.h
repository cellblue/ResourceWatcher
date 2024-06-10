#include <vector>
#include <memory>
#include "watcher.h"
#include "timer_manager.h"
namespace resource_watcher {

class App{
private:
    std::vector<std::unique_ptr<Watcher> > watchers_;
    std::unique_ptr<TimerManager> timer_manager_;
public:
    App();
    void start();
    void stop();
};

};