#include "fcfs.h"
#include <limits>

FCFS::FCFS(std::vector<process>& processes_ref)
    : processes(processes_ref), current_time(0), current_index(-1),
      current_burst_remaining(0), processing(false) {}

int FCFS::get_process() {
    // Check if all processes are completed (we consider finish_time > 0 as completed)
    bool all_done = true;
    for (const auto& p : processes) {
        if (p.finish_time == 0 && p.burst_time > 0) {
            all_done = false;
            break;
        }
    }
    if (all_done) return -2;

    // If no process is currently running, find the next available one
    if (!processing) {
        int earliest_arrival = std::numeric_limits<int>::max();
        int next_index = -1;

        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].finish_time == 0 && processes[i].arrival_time <= current_time) {
                if (processes[i].arrival_time < earliest_arrival ||
                    (processes[i].arrival_time == earliest_arrival && processes[i].pid < processes[next_index].pid)) {
                    earliest_arrival = processes[i].arrival_time;
                    next_index = i;
                }
            }
        }
        if (next_index == -1) {
            current_time++;
            return -1; // Idle
        } else {
            current_index = next_index;
            current_burst_remaining = processes[current_index].burst_time;
            processing = true;
        }
    }
    // Execute the current process
    current_burst_remaining--;
    int running_id = processes[current_index].pid;
    current_time++;

    // If process is done
    if (current_burst_remaining == 0) {
        int end_time = current_time;
        processes[current_index].finish_time = end_time;
        processes[current_index].turn_around_time = end_time - processes[current_index].arrival_time;
        processes[current_index].waiting_time = processes[current_index].turn_around_time - processes[current_index].burst_time;
        processing = false;
    }
    return running_id;
}
