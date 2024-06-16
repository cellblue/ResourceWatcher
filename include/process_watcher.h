#pragma once

#include "watcher.h"

namespace resource_watcher{
class ProcessWatcher:public Watcher{
public:
    ProcessWatcher();
    virtual void dataCollection();
};
};