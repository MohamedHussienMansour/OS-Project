#include "round_robin.h"

round_robin::round_robin(vector<process> &processes_ref, int q)
    : processes(processes_ref), quantum(q) {
    time = 0;
    is_busy = false;
    curr_process = nullptr;
    time_slice = 0;
}

bool round_robin::all_finished() {
    for (auto &p : processes) {
        if (p.burst_time > 0) return false;
    }
    return true;
}

int round_robin::get_process() {
    if (all_finished()) return -2;

    for (auto &p : processes) {
        if (p.arrival_time == time) ready.push(&p);
    }

    if (!is_busy || time_slice == quantum) {
        if (curr_process && curr_process->burst_time > 0) {
            ready.push(curr_process);
        }

        if (!ready.empty()) {
            curr_process = ready.front();
            ready.pop();
            is_busy = true;
            time_slice = 0;
        } else {
            curr_process = nullptr;
            is_busy = false;
        }
    }

    if (is_busy && curr_process) {
        int current_id = curr_process->pid;
        curr_process->burst_time--;
        time_slice++;

        if (curr_process->burst_time == 0) {
            curr_process->finish_time = time + 1;
            curr_process->calculate_turn_time();
            curr_process->calculate_waiting_time();
            curr_process = nullptr;
            is_busy = false;
            time_slice = 0;
            time++;
            return current_id;
        }

        time++;
        return curr_process ? current_id : -1;
    }

    time++;
    return -1;
}
