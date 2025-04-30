#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "process.h"  // Include the class definition

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
