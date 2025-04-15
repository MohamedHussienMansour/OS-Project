#include "fcfs.h"

FCFS::FCFS(std::vector<process> &processes_ref) : processes(processes_ref) {
    time = 0;
    current = nullptr;
}

bool FCFS::all_finished() {
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (processes[i].burst_time != 0)
            return false;
    }
    return true;
}

int FCFS::get_process() {
    if (all_finished()) {
        return -2;
    }

    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (time == processes[i].arrival_time)
            ready.push(&processes[i]);
    }

    time++;

    if (!ready.empty()) {
        current = ready.front();
        current->burst_time--;

        if (current->burst_time == 0) {
            ready.pop();
            current->finish_time = time;
            current->calculate_turn_time();
            current->calculate_waiting_time();
        }

        return current->pid;
    } else {
        return -1;
    }
}
