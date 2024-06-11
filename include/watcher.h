#include <string>
#include <any>
#include <map>
#include <filesystem>
#include <memory>
#include "system_data.pb.h"
namespace resource_watcher{
class Watcher{
private:
    std::shared_ptr<system_data> sys_data_; 
public:
    virtual void dataCollection();
};
};