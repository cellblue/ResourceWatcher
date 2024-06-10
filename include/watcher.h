#include <string>
#include <any>
#include <map>
#include <filesystem>

namespace resource_watcher{
class Watcher{
private:
    std::string pid_;
public:
    virtual void getData(std::map<std::string,std::any> &data) = 0;
};
};