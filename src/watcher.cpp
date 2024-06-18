#include "watcher.h"

namespace resource_watcher{
std::shared_ptr<SystemData> Watcher::sys_data_ = std::make_shared<SystemData>();


} // namespace resource_watcher