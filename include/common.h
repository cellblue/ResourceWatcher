#pragma once

#include <string>

namespace resource_watcher {
constexpr std::string_view cpu_stat = "/proc/stat";
constexpr std::string_view cpu_info = "/proc/cpuinfo";

constexpr std::string_view mem_info = "/proc/meminfo";

constexpr std::string_view proc = "/proc";
} // namespace resource_watcher