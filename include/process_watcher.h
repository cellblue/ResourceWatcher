#pragma once

#include "watcher.h"

namespace resource_watcher{
class ProcessWatcher:public Watcher{
public:
    ProcessWatcher() = default;
    virtual void dataCollection();
private:
    void readProcDir();
    std::map<char, int> proc_stat_;
};
} // namespace resource_watcher