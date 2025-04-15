#ifndef PROCESS_H
#define PROCESS_H

class process {
public:
    int pid;
    int burst_time;
    int waiting_time;
    int arrival_time;
    int finish_time;
    int turn_around_time;
    int priority;
    int copy_burst_time;

    process(int pid, int arrival_time = 0, int burst_time = 0, int priority = 5);

    int burst_time_now();
    void calculate_waiting_time();
    void calculate_turn_time();
};

#endif // PROCESS_H
