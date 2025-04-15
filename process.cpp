#include "process.h"

process::process(int pid, int arrival_time, int burst_time, int priority) {
    this->pid = pid;
    this->priority = priority;
    this->burst_time = burst_time;
    this->waiting_time = 0;
    this->arrival_time = arrival_time;
    this->finish_time = 0;
    this->copy_burst_time = burst_time;
    this->turn_around_time = 0;
}

int process::burst_time_now() {
    return copy_burst_time;
}

void process::calculate_waiting_time() {
    this->waiting_time = finish_time - arrival_time - copy_burst_time;
}

void process::calculate_turn_time() {
    this->turn_around_time = finish_time - arrival_time;
}
