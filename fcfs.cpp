#include "fcfs.h"

FCFS::FCFS(std::vector<process>& processes_ref) 
    : processes(processes_ref), current_index(0), current_burst_remaining(0) {}

int FCFS::get_process() {
    // If all processes are done
    if (current_index >= processes.size())
        return -2;

    // Initialize burst time of current process if first time visiting
    if (current_burst_remaining == 0)
        current_burst_remaining = processes[current_index].burst_time;

    // Simulate execution
    current_burst_remaining--;

    // Process ID to return
    int current_id = processes[current_index].id;

    // If process finished
    if (current_burst_remaining == 0) {
        // Calculate TAT and WT
        int end_time = 0;
        for (int i = 0; i <= current_index; ++i)
            end_time += processes[i].burst_time;

        processes[current_index].turn_around_time = end_time - processes[current_index].arrival_time;
        processes[current_index].waiting_time = processes[current_index].turn_around_time - processes[current_index].burst_time;

        current_index++;
    }

    return current_id;
}
