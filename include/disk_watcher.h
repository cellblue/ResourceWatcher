#pragma once

#include "watcher.h"

namespace resource_watcher{
class DiskWatcher:public Watcher{
public:
    DiskWatcher();
    virtual void dataCollection();
};
};