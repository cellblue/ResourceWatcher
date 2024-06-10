#include "watcher.h"
#include <any>


namespace resource_watcher{
class CPUWatcher:public Watcher{
private:
    
public:
    CPUWatcher();
    double getCPUusage();
    virtual void dataCollection();
};
};