#include "fcfs.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Process> processes = {
        Process(1, 0, 4),
        Process(2, 1, 3),
        Process(3, 2, 1)
    };

    FCFS_Scheduler scheduler(processes);

    while (true) {
        int pid = scheduler.get_process();
        if (pid == -2) break;
        if (pid == -1)
            std::cout << "Time Idle\n";
        else
            std::cout << "Time PID " << pid << "\n";
    }

    scheduler.print_report();
    return 0;
}
