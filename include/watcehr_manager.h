#include <vector>
#include <memory>
#include "watcher.h"
namespace resource_watcher {

class WatcherManager{
private:
    std::vector<std::unique_ptr<Watcher> > watchers_;
public:
    WatcherManager();
};

};