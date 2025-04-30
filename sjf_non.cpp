#include "sjf_non.h"

sjf_non::sjf_non(std::vector<process>& processes_ref)
    : processes(processes_ref), time(0), is_busy(false), curr_process(nullptr) {}

bool sjf_non::all_finished() {
    for (const auto& p : processes) {
        if (p.burst_time != 0) return false;
    }
    return true;
}

bool sjf_non::priority_sorting(process* p1, process* p2) {
    return p1->burst_time < p2->burst_time;
}

int sjf_non::get_process() {
    if (all_finished()) return -2;

    // Check for newly arrived processes
    for (auto& p : processes) {
        if (p.arrival_time == time) {
            ready.push_back(&p);
        }
    }

    time++;

    if (!is_busy) {
        std::sort(ready.begin(), ready.end(), sjf_non::priority_sorting);

        if (!ready.empty()) {
            is_busy = true;
            curr_process = ready.front();
            ready.erase(ready.begin());

            curr_process->burst_time--;
            if (curr_process->burst_time == 0) {
                is_busy = false;
                curr_process->finish_time = time;
                curr_process->calculate_turn_time();
                curr_process->calculate_waiting_time();
            }

            return curr_process->pid;
        } else {
            return -1; // CPU idle
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

    return -1; // Fallback
}
