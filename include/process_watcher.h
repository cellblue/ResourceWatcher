#include "watcher.h"

namespace resource_watcher{
class ProcessWatcher:public Watcher{
public:
    ProcessWatcher();
    virtual void getData(std::map<std::string,std::any>& data);
};
};