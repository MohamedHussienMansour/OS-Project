#include "priority_non.h"
#include "process.h"

priority_non::priority_non(vector<process> &processes_ref)
    : processes(processes_ref) {
    time = 0;
    is_busy = false;
}

bool priority_non::all_finished() {
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (processes[i].burst_time != 0) return false;
    }
    return true;
}

bool priority_non::priority_sorting(process *p1, process *p2) {
    return p1->priority < p2->priority;
}

int priority_non::get_process() {
    if (all_finished()) {
        return -2;
    }

    int n = processes.size();
    for (int i = 0; i < n; i++) {
        if (time == processes[i].arrival_time)
            waiting.push_back(&processes[i]);
    }

    time++;
    if (!is_busy) {
        sort(waiting.begin(), waiting.end(), priority_non::priority_sorting);
        if (!waiting.empty()) {
            is_busy = true;
            curr_process = waiting[0];
            waiting.erase(waiting.begin());
            curr_process->burst_time--;
            if (curr_process->burst_time == 0) {
                is_busy = false;
                curr_process->finish_time = time;
                curr_process->calculate_turn_time();
                curr_process->calculate_waiting_time();
            }
            return curr_process->pid;
        } else {
            return -1;
        }
    } else {
        curr_process->burst_time--;
        if (curr_process->burst_time == 0) {
            is_busy = false;
            curr_process->finish_time = time;
            curr_process->calculate_turn_time();
            curr_process->calculate_waiting_time();
        }
        return curr_process->pid;
    }

    return -1;
}
