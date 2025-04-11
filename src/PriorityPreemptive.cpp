//
// Created by Ahmed Hussein on 4/9/2025.
//

#include "PriorityPreemptive.h"


PreemptivePriorityScheduler:: PreemptivePriorityScheduler(std::vector<Process *> processes) : processes(processes) {
    std::sort(processes.begin(), processes.end(),[] (Process *p1, Process *p2) -> bool{
        return p1->get_start_time() < p2->get_start_time(); // sort the processes by start time
        });
    // Initialize the process queue with the given processes
    for (const auto process : processes) {
        if(add_process(process)){
            last_added_process++;
        }
        else break; // the start time hasn't come
    }
}


bool PreemptivePriorityScheduler::add_process(Process *newProcess) {
    if(newProcess->get_start_time() == time){
        // add the process to the priority queue when its start time has come
        newProcess->set_remaining_burst_time(newProcess->get_burst_time()); // set the remaining burst time
        processQueue.push(newProcess);

        // increment number of processes
        num_process++;

        return true; // process added
    }
    return false; // process not added
}


int PreemptivePriorityScheduler::schedule_next_time_step() {
    int ret; // return value

    //add not added processes from the vector
    for(int i=last_added_process+1; i<processes.size(); i++){
        if(add_process(processes[i]))
            last_added_process++;
    }
    // check if there is a process to be scheduled
    if(!processQueue.empty()){
        Process *process = processQueue.top();

        // decrease remaining time by 1
        process->set_remaining_burst_time(process->get_remaining_burst_time() - 1);

        // remove the process if it has finished
        if (process->get_remaining_burst_time() == 0) {
            process->set_end_time(time);
            processQueue.pop();
        }

        // return the scheduled process ID
        ret = process->get_pid();

    }
    else if(last_added_process < (int)(processes.size()-1)){
            ret = -1; // Process queue is empty but there will be process in the future
    }
    else { // all process has been scheduled and finished
        return -2; // no process to schedule
    }
    // increase the time
    time += 1;
    return ret;
}


float PreemptivePriorityScheduler::get_turnaround_time() {
    if(num_process==0) return 0; // no processes to calculate turnaround time for

    // calculate the average turnaround time
    float totalTurnaroundTime = 0;
    for (const auto& process : processes) {
        totalTurnaroundTime += (float)process->get_turnaround_time();
    }
    return totalTurnaroundTime / (float)num_process;
}


float PreemptivePriorityScheduler::get_waiting_time() {
    if(num_process==0) return 0; // no processes to calculate waiting time for

    // calculate the average waiting time
    float totalWaitingTime = 0;
    for (const auto& process : processes) {
        totalWaitingTime += (float)process->get_waiting_time();
    }
    return totalWaitingTime / (float)num_process;
}