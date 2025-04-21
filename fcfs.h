#ifndef FCFS_H
#define FCFS_H

#include <vector>

struct process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;  // used in main, even if not relevant to FCFS
    int waiting_time;
    int turn_around_time;
    bool completed;

    process(int i, int a, int b, int p)
        : id(i), arrival_time(a), burst_time(b), priority(p),
          waiting_time(0), turn_around_time(0), completed(false) {}
};

class FCFS {
private:
    std::vector<process>& processes;
    int current_time;
    int current_index;
    int current_burst_remaining;
    bool processing;

public:
    FCFS(std::vector<process>& processes_ref);
    int get_process(); // returns -2 if all done, -1 if idle, or the current process ID
};

#endif // FCFS_H
