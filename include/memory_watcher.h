#pragma once

#include "watcher.h"

namespace resource_watcher{
class MemoryWatcher:public Watcher{
public:
    MemoryWatcher();
    virtual void dataCollection();
};
} // namespace resource_watcher