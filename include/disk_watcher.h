#include "watcher.h"

namespace resource_watcher{
class DiskWatcher:public Watcher{
public:
    DiskWatcher();
    virtual void getData(std::map<std::string,std::any>& data);
};
};