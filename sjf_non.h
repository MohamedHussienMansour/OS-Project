#pragma once
#include <vector>
#include "process.h"
#include <algorithm>

class sjf_non {
public:
    sjf_non(std::vector<process>& processes_ref);

    int get_process();
    bool all_finished();

private:
    static bool priority_sorting(process* p1, process* p2);

    std::vector<process>& processes;
    std::vector<process*> ready;
    int time;
    bool is_busy;
    process* curr_process;
};
