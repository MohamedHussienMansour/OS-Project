#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <vector>
#include <queue>
using namespace std;

#include "process.h" // Include your process class definition here

class round_robin {
public:
    vector<process> &processes;
    queue<process*> ready;
    int time;
    bool is_busy;
    process *curr_process;
    int quantum;
    int time_slice;

    round_robin(vector<process> &processes_ref, int q);
    bool all_finished();
    int get_process();
};

#endif // ROUND_ROBIN_H
