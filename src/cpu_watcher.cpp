#include "cpu_watcher.h"
#include <filesystem>
#include <fstream>
#include <thread>
#include <ranges>
#include <numeric>
#include "common.h"
namespace resource_watcher{


/*
message CPU {
    optional string name = 1; // CPU seq 
    optional float usage = 2;
    optional float user_usage = 3;
    optional float system_usage = 4;
    optional float irq_usage = 5;
    optional float softirq_usage = 6;
    optional int32 running_time = 7;
}
*/

double CPUWatcher::getCPUusage(){
    // user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
    auto readStats = [&]() {
        std::ifstream file(cpu_stat.data());
        std::string line;
        std::getline(file, line);
        std::string_view sv{line};
        std::vector<long> values;
        for (auto token = sv.find_first_not_of(' '); token != std::string_view::npos; ) {
            auto next_token = sv.find(' ', token);
            values.push_back(std::stol(std::string(sv.substr(token, next_token - token))));
            token = sv.find_first_not_of(' ', next_token);
        }
        return values;
    };
    
    auto startValues = readStats();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto endValues = readStats(); 

    auto diff_view = std::ranges::zip(endValues, startValues) | std::ranges::views::transform([](auto&& pair) {
        return std::get<0>(pair) - std::get<1>(pair);
    });

    auto total_diff = std::accumulate(diff_view.begin(), diff_view.end(), 0);
    auto stop_diff = diff_view[3]+diff_view[4];

    return (1-stop_diff/total_diff)*100;
}
void CPUWatcher::dataCollection(){
    // 获取cpu个数 
    const unsigned int num_cpus = std::thread::hardware_concurrency();
    

}
};