#include "watcher.h"

namespace resource_watcher{
std::shared_ptr<system_data> Watcher::sys_data_ = std::make_shared<system_data>();


} // namespace resource_watcher