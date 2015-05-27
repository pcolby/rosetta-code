#include <iostream>
#include <numeric>
#include <fstream>
#include <unistd.h>
#include <vector>

std::vector<size_t> get_cpu_times() {
    std::vector<size_t> times;
    std::ifstream proc_stat("/proc/stat");
    if (proc_stat.is_open()) {
        proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
        for (size_t time; proc_stat >> time; times.push_back(time));
    }
    return times;
}

int main(int, char *[]) {
    size_t previous_idle_time=0, previous_total_time=0;
    while (true) {
        const std::vector<size_t> cpu_times = get_cpu_times();
        const size_t current_idle_time = cpu_times[3];
        const size_t current_total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
        const float idle_time_delta = current_idle_time - previous_idle_time;
        const float total_time_delta = current_total_time - previous_total_time;
        const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
        std::cout << utilization << '%' << std::endl;
        previous_idle_time = current_idle_time;
        previous_total_time = current_total_time;
        sleep(1);
    }
}
