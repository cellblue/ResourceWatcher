#include "watcher.h"

namespace resource_watcher{
class MemoryWatcher:public Watcher{
public:
    MemoryWatcher();
    virtual void getData(std::map<std::string,std::any>& data);
};
};