#include "sjf_preemptive.h"
#include <algorithm>

sjf_preemptive::sjf_preemptive(std::vector<process>& processes_ref)
    : processes(processes_ref), time(0), curr_process(nullptr) {}

bool sjf_preemptive::all_finished() {
    for (const auto& p : processes) {
        if (p.burst_time != 0) return false;
    }
    return true;
}

bool sjf_preemptive::priority_sorting(process* p1, process* p2) {
    return p1->burst_time < p2->burst_time;
}

int sjf_preemptive::get_process() {
    if (all_finished()) return -2;

    // Check for newly arrived processes
    for (auto& p : processes) {
        if (p.arrival_time == time) {
            ready.push_back(&p);
        }
    }

    time++;

    std::sort(ready.begin(), ready.end(), sjf_preemptive::priority_sorting);

    if (!ready.empty()) {
        curr_process = ready.front();
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

    return -1; // fallback
}
