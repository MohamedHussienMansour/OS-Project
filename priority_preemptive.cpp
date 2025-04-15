#include "priority_preemptive.h"

priority_preemptive::priority_preemptive(std::vector<process> &processes_ref)
    : processes(processes_ref) {
    time = 0;
}

bool priority_preemptive::all_finished() {
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (processes[i].burst_time != 0)
            return false;
    }
    return true;
}

bool priority_preemptive::priority_sorting(process *p1, process *p2) {
    return p1->priority < p2->priority;
}

int priority_preemptive::get_process() {
    if (all_finished()) {
        return -2;
    }

    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (time == processes[i].arrival_time)
            ready.push_back(&processes[i]); // Add new arrivals
    }

    time++;
    std::sort(ready.begin(), ready.end(), priority_sorting); // Sort ready queue by priority

    if (!ready.empty()) {
        curr_process = ready[0];
        curr_process->burst_time--;
        if (curr_process->burst_time == 0) {
            ready.erase(ready.begin());
            curr_process->finish_time = time;
            curr_process->calculate_turn_time();
            curr_process->calculate_waiting_time();
        }
        return curr_process->pid;
    } else {
        return -1; // CPU idle
    }
}
