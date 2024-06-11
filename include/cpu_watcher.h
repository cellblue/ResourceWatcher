#include "watcher.h"
#include <any>


namespace resource_watcher{
class CPUWatcher:public Watcher{
public:
    CPUWatcher();
    virtual void dataCollection();
};
};