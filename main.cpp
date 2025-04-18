#include "fcfs.h"
#include <iostream>

int main() {
    FCFS_Scheduler scheduler;

    // Fixed scenario for testing
    scheduler.add_process(1, 0, 4);
    scheduler.add_process(2, 1, 3);
    scheduler.add_process(3, 2, 1);
    scheduler.add_process(4, 5, 2);

    scheduler.run();
    scheduler.print_report();

    return 0;
}
