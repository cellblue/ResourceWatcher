#pragma once

#include "watcher.h"
#include <any>
#include <optional>

namespace resource_watcher{
class CPUWatcher:public Watcher{
public:
    CPUWatcher() = default;
    void dataCollection() override;
private:
    enum class CpuTimeType : uint32_t {
        User,
        Nice,
        System,
        Idle,
        IoWait,
        Irq,
        SoftIrq,
        Steal,
        Guest,
        GuestNice,
        Total,
        Count 
    };
    
    struct CpuStat {
        std::array<uint32_t, static_cast<size_t>(CpuTimeType::Count)> times;
        
        const uint32_t& operator[](CpuTimeType type) const {
            return times[static_cast<size_t>(type)];
        }   
    
        uint32_t& operator[](CpuTimeType type) {
            return times[static_cast<size_t>(type)];
        }

    }start_cpu_stat_,end_cpu_stat_;


    CpuStat readCpuStat();
    float getUsage();
    float getUserUsage();
    float getSystemUsage();
    float getIrqUsage();
    float getSoftirqUsage();
    uint32_t getRunningTime();
};
} // namespace resource_watcher