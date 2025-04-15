#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <queue>
#include "process.h"

class FCFS {
public:
    std::vector<process> &processes;
    std::queue<process*> ready;
    process *current;
    int time;

    FCFS(std::vector<process> &processes_ref);

    bool all_finished();
    int get_process();
};

#endif // FCFS_H
