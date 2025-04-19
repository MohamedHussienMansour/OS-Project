#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <iostream>

struct process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;

    // Constructor that takes 4 parameters
    process(int id, int arrival_time, int burst_time, int completion_time)
        : id(id), arrival_time(arrival_time), burst_time(burst_time), completion_time(completion_time) {}

    // Default constructor for the main.cpp
    process() : id(0), arrival_time(0), burst_time(0), completion_time(0) {}

    // Function to calculate turnaround time
    void calculate_turn_time() {
        turn_around_time = completion_time - arrival_time;
    }

    // Function to calculate waiting time
    void calculate_waiting_time() {
        waiting_time = turn_around_time - burst_time;
    }

    int turn_around_time; // Turnaround time
    int waiting_time;     // Waiting time
};

class FCFS {
    public:
        FCFS(std::vector<process>& processes_ref);
        int get_process();  // Returns the next process ID or -2 when done
    private:
        std::vector<process>& processes;
        int current_index;
        int current_burst_remaining;
    };

#endif // FCFS_H
