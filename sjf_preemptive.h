#pragma once
#include <vector>
#include "process.h"
#include <algorithm>

class sjf_preemptive {
public:
    sjf_preemptive(std::vector<process>& processes_ref);

    int get_process();
    bool all_finished();

private:
    static bool priority_sorting(process* p1, process* p2);

    std::vector<process>& processes;
    std::vector<process*> ready;
    int time;
    process* curr_process;
};
