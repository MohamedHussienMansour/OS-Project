#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <queue>

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;

    Process(int id, int arrival, int burst);
    void calculate_turn_time();         // added
    void calculate_waiting_time();      // added
};

class FCFS_Scheduler {
private:
    std::vector<Process>& processes;
    std::queue<Process*> ready;
    Process* current;
    int time;

    bool all_finished();

public:
    FCFS_Scheduler(std::vector<Process>& processes_ref); // changed constructor
    int get_process();
    void print_report();
};

#endif // FCFS_H
