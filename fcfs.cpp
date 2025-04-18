#include "fcfs.h"
#include <iostream>

using namespace std;

Process::Process(int id, int arrival, int burst)
    : pid(id), arrival_time(arrival), burst_time(burst), remaining_time(burst),
      start_time(-1), finish_time(0), waiting_time(0), turnaround_time(0) {}

void Process::calculate_times() {
    turnaround_time = finish_time - arrival_time;
    waiting_time = turnaround_time - burst_time;
}

FCFS_Scheduler::FCFS_Scheduler() {
    time = 0;
    current = nullptr;
}

void FCFS_Scheduler::add_process(int pid, int arrival_time, int burst_time) {
    processes.emplace_back(pid, arrival_time, burst_time);
}

bool FCFS_Scheduler::all_finished() {
    for (const auto& p : processes) {
        if (p.remaining_time > 0)
            return false;
    }
    return true;
}

void FCFS_Scheduler::run() {
    cout << "\nRunning FCFS Scheduler...\n";
    cout << "Time\tRunning PID\n";

    while (!all_finished()) {
        for (auto& p : processes) {
            if (p.arrival_time == time)
                ready_queue.push(&p);
        }

        if (current == nullptr && !ready_queue.empty()) {
            current = ready_queue.front();
            ready_queue.pop();
            if (current->start_time == -1)
                current->start_time = time;
        }

        if (current != nullptr) {
            cout << time << "\t" << current->pid << endl;
            current->remaining_time--;

            if (current->remaining_time == 0) {
                current->finish_time = time + 1;
                current->calculate_times();
                current = nullptr;
            }
        } else {
            cout << time << "\tIdle\n";
        }

        time++;
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
