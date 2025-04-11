//
// Created by Ahmed Hussein on 4/9/2025.
//

#include "Process.h"

int Process::processCounter = 0; // initialize counter to 0

Process::Process(int startTime, int priority, int burstTime) {
    this->startTime = startTime;
    this->priority = priority;
    this->pid = processCounter++;
    this->burstTime = burstTime;
}

int Process::get_turnaround_time() {
    return endTime - startTime;
}

int Process::get_waiting_time() {
    return get_turnaround_time() - burstTime;
}

// Setters
void Process::set_end_time(int endTime) {
    this->endTime = endTime;
}
void Process::set_burst_time(int burstTime) {
    this->burstTime = burstTime;
}
void Process::set_remaining_burst_time(int remainingBurstTime) {
    this->remainingBurstTime = remainingBurstTime;
}

// Getters
int Process::get_remaining_burst_time(){
    return remainingBurstTime;
}
int Process::get_burst_time(){
    return burstTime;
}
int Process::get_start_time() {
    return startTime;
}
int Process::get_priority(){
    return priority;
}
int Process::get_pid() {
    return pid;
}