#include "watcher.h"

namespace resource_watcher{
class CPUWatcher:public Watcher{
public:
    CPUWatcher();
    virtual void getData(std::map<std::string,std::any>& data);
};
};