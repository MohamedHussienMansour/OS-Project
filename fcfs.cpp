#include "fcfs.h"
#include <iostream>

using namespace std;

Process::Process(int id, int arrival, int burst)
    : pid(id), arrival_time(arrival), burst_time(burst), remaining_time(burst),
      start_time(-1), finish_time(0), waiting_time(0), turnaround_time(0) {}

void Process::calculate_turn_time() {
    turnaround_time = finish_time - arrival_time;
}

void Process::calculate_waiting_time() {
    waiting_time = turnaround_time - burst_time;
}

FCFS_Scheduler::FCFS_Scheduler(std::vector<Process>& processes_ref)
    : processes(processes_ref) {
    time = 0;
    current = nullptr;
}

bool FCFS_Scheduler::all_finished() {
    for (const auto& p : processes) {
        if (p.remaining_time > 0)
            return false;
    }
    return true;
}

int FCFS_Scheduler::get_process() {
    if (all_finished()) {
        return -2;
    }

    for (auto& p : processes) {
        if (p.arrival_time == time)
            ready.push(&p);
    }

    time++;

    if (!ready.empty()) {
        current = ready.front();
        current->remaining_time--;

        if (current->start_time == -1)
            current->start_time = time - 1;

        if (current->remaining_time == 0) {
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

void FCFS_Scheduler::print_report() {
    cout << "\nFinal FCFS Scheduling Results:\n";
    cout << "PID\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.start_time << "\t" << p.finish_time << "\t\t"
             << p.waiting_time << "\t" << p.turnaround_time << endl;
    }
}
