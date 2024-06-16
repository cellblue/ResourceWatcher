#include "cpu_watcher.h"
#include <filesystem>
#include <fstream>
#include <thread>
#include <ranges>
#include <cassert>
#include <numeric>
#include "common.h"
namespace resource_watcher{

CPUWatcher::CpuStat CPUWatcher::getCpuStat(){
    std::ifstream file(cpu_stat.data());
    std::string line;
    std::getline(file, line);
    std::string_view sv{line};
    CpuStat values;
    int index = 0;
    for (auto token = sv.find_first_not_of(' '); token != std::string_view::npos; ) {
        auto next_token = sv.find(' ', token);
        values[static_cast<CpuTimeType>(index)] = std::stol(std::string(sv.substr(token, next_token - token)));
        values[CpuTimeType::Total] += values[static_cast<CpuTimeType>(index)];
        index++;
        token = sv.find_first_not_of(' ', next_token);
    }
    return values;
}   

float CPUWatcher::getUsage(){
    unsigned long total_start = start_cpu_stat_[CpuTimeType::Total];
    unsigned long total_end = end_cpu_stat_[CpuTimeType::Total];
    unsigned long idle_start = start_cpu_stat_[CpuTimeType::Idle] + start_cpu_stat_[CpuTimeType::IoWait];
    unsigned long idle_end = end_cpu_stat_[CpuTimeType::Idle] + end_cpu_stat_[CpuTimeType::IoWait];
    
    float total_diff = total_end-total_start;
    float idle_diff = idle_end-idle_start;

    return (1.0 - idle_diff/total_diff)*100;
}

float CPUWatcher::getUserUsage(){
    float total_diff = end_cpu_stat_[CpuTimeType::Total] - start_cpu_stat_[CpuTimeType::Total];
    float user_diff = end_cpu_stat_[CpuTimeType::User] - start_cpu_stat_[CpuTimeType::User];

    return user_diff/total_diff*100;
}

float CPUWatcher::getSystemUsage(){
    float total_diff = end_cpu_stat_[CpuTimeType::Total] - start_cpu_stat_[CpuTimeType::Total];
    float system_diff = end_cpu_stat_[CpuTimeType::System] - start_cpu_stat_[CpuTimeType::System];

    return system_diff/total_diff*100;
}

float CPUWatcher::getIrqUsage(){
    float total_diff = end_cpu_stat_[CpuTimeType::Total] - start_cpu_stat_[CpuTimeType::Total];
    float irq_diff = end_cpu_stat_[CpuTimeType::Irq] - start_cpu_stat_[CpuTimeType::Irq];

    return irq_diff/total_diff*100;
}

float CPUWatcher::getSoftirqUsage(){
    float total_diff = end_cpu_stat_[CpuTimeType::Total] - start_cpu_stat_[CpuTimeType::Total];
    float softirq_diff = end_cpu_stat_[CpuTimeType::SoftIrq] - start_cpu_stat_[CpuTimeType::SoftIrq];

    return softirq_diff/total_diff*100;
}

uint32_t CPUWatcher::getRunningTime(){
    unsigned long total_end = end_cpu_stat_[CpuTimeType::User] + end_cpu_stat_[CpuTimeType::Nice] + end_cpu_stat_[CpuTimeType::System] + end_cpu_stat_[CpuTimeType::Idle] + end_cpu_stat_[CpuTimeType::IoWait] + end_cpu_stat_[CpuTimeType::Irq] + end_cpu_stat_[CpuTimeType::SoftIrq];
    return total_end;
}

void CPUWatcher::dataCollection(){
    // 获取cpu个数 
    const unsigned int num_cpus = std::thread::hardware_concurrency();
    // 获取sys_cpu
    auto sys_cpu = Watcher::sys_data_->mutable_sys_cpu();

    start_cpu_stat_ = getCpuStat();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    end_cpu_stat_ = getCpuStat(); 

    sys_cpu->set_name("sys_cpu");
    sys_cpu->set_usage(getUsage());
    sys_cpu->set_user_usage(getUserUsage());
    sys_cpu->set_system_usage(getSystemUsage());
    sys_cpu->set_irq_usage(getIrqUsage());
    sys_cpu->set_softirq_usage(getSoftirqUsage());
    sys_cpu->set_running_time(getRunningTime());

}
};