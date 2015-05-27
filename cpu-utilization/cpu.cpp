#include <iostream>
#include <numeric>
#include <fstream>
#include <unistd.h>
#include <vector>

std::vector<size_t> get_cpu_times() {
    std::vector<size_t> times;
    std::ifstream proc_stat("/proc/stat");
    if (proc_stat.is_open()) {
        std::string name;
        proc_stat >> name;
        for (size_t time; proc_stat >> time; times.push_back(time));
    }
    return times;
}

int main(int, char *[]) {
    size_t prev_idle_time=0, prev_total_time=0;
    while (true) {
        const std::vector<size_t> cpu_times = get_cpu_times();
        const size_t idle_time = cpu_times[3];
        const size_t total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
        const float utilization = 100.0 * (1.0 - (idle_time - prev_idle_time) / static_cast<float>(total_time - prev_total_time));
        std::cout << utilization << '%' << std::endl;
        prev_idle_time = idle_time;
        prev_total_time = total_time;
        sleep(1);
    }
}
