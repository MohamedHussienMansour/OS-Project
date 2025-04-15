#ifndef PRIORITY_PREEMPTIVE_H
#define PRIORITY_PREEMPTIVE_H

#include <vector>
#include <algorithm>
#include "process.h" // Make sure this defines the `process` class

class priority_preemptive {
public:
    std::vector<process> &processes;
    std::vector<process*> ready;
    int time;
    process *curr_process;

    priority_preemptive(std::vector<process> &processes_ref);

    bool all_finished();
    static bool priority_sorting(process *p1, process *p2);
    int get_process();
};

#endif // PRIORITY_PREEMPTIVE_H
