#include "fcfs.h"           // Include the header file where the FCFS class and process struct are defined
#include <limits>           // For std::numeric_limits to get maximum integer value

// Constructor for FCFS class
// Initializes member variables with reference to processes, and sets initial states
FCFS::FCFS(std::vector<process>& processes_ref)
    : processes(processes_ref), current_time(0), current_index(-1),
    current_burst_remaining(0), processing(false) {
    for (int i = 0; i < processes.size(); ++i) {
        processes[i].finish_time=0;
    }
}

// Function that simulates one unit of CPU time and returns the PID of the process being executed
int FCFS::get_process() {

    // Check if all processes are completed
    // A process is considered completed if finish_time > 0
    bool all_done = true;
    for (const auto& p : processes) {
        if (p.finish_time == 0 && p.burst_time > 0) {
            all_done = false;
            break;
        }
    }

    // If all processes are done, return -2 to indicate simulation is complete
    if (all_done) return -2;

    // If no process is currently being executed, find the next eligible process
    if (!processing) {
        int earliest_arrival = std::numeric_limits<int>::max(); // Initialize to a very large value
        int next_index = -1;  // Index of the next process to schedule

        // Loop through all processes to find the one with the earliest arrival time that hasn't finished
        for (int i = 0; i < processes.size(); ++i) {
            // Process must not be finished and must have arrived by current_time
            if (processes[i].finish_time == 0 && processes[i].arrival_time <= current_time) {
                // Choose the process with the earliest arrival time, or smallest PID in case of a tie
                if (processes[i].arrival_time < earliest_arrival ||
                    (processes[i].arrival_time == earliest_arrival && processes[i].pid < processes[next_index].pid)) {
                    earliest_arrival = processes[i].arrival_time;
                    next_index = i;
                }
            }
        }

        // If no eligible process found, CPU is idle this time unit
        if (next_index == -1) {
            current_time++;    // Advance the simulation time
            return -1;         // Return -1 to indicate CPU is idle
        } else {
            // Start executing the selected process
            current_index = next_index;
            current_burst_remaining = processes[current_index].burst_time;
            processing = true;
        }
    }

    // Execute the current process for one unit of time
    current_burst_remaining--;                             // Decrease remaining burst time
    int running_id = processes[current_index].pid;         // Store the PID of the running process
    current_time++;                                        // Advance simulation time

    // If the process finishes execution
    if (current_burst_remaining == 0) {
        int end_time = current_time;   // Record finish time
        processes[current_index].finish_time = end_time;
        processes[current_index].turn_around_time = end_time - processes[current_index].arrival_time;
        processes[current_index].waiting_time = processes[current_index].turn_around_time - processes[current_index].burst_time;
        processing = false;            // Mark CPU as idle
    }
    // Return PID of the process that was run this time unit
    return running_id;
}
