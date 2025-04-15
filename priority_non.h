#ifndef PRIORITY_NON_H
#define PRIORITY_NON_H

#include <vector>
#include <algorithm>
#include "process.h"

using std::vector;
using std::sort;

class priority_non {
public:
    vector<process> &processes;
    vector<process*> waiting;
    int time;
    bool is_busy;
    process *curr_process;

    priority_non(vector<process> &processes_ref);

    bool all_finished();
    static bool priority_sorting(process *p1, process *p2);
    int get_process();
};

#endif // PRIORITY_NON_H
