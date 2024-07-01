#pragma once
#include <memory>
#include "system_data.pb.h"
namespace resource_watcher{
class ResourceData{
public:
    template<typename T>
    void update(T&&);
private:
    void notify();
    static std::shared_ptr<SystemData> sys_data_; 
};

}