//
// Created by Ahmed Hussein on 4/9/2025.
//

#ifndef OS_PROJECT_PRIORITYPREEMPTIVE_H
#define OS_PROJECT_PRIORITYPREEMPTIVE_H

#include "Process.h"
#include <vector>
#include <queue>
#include <algorithm>

class PreemptivePriorityScheduler {
private:
    int num_process=0;
    int time = 0;
    int last_added_process = -1; // index of the next process to be added from the vector

    // custom comparator for the priority queue
    struct ComparePriority {
        bool operator()(Process *p1, Process *p2) {
            return p1->get_priority() > p2->get_priority(); // lower number hase higher priority
        }
    };

    std::priority_queue<Process *, std::vector<Process *>, ComparePriority> processQueue; // min heap
    std::vector<Process *> processes; // vector of processes

public:
    /**@brief Constructor for the PreemptivePriorityScheduler class
     *
     * @param processes vector of processes
     */
    PreemptivePriorityScheduler(std::vector<Process *> processes);

    /** @brief Add a new process to the scheduler
     *
     * The method adds a process to the scheduler's process queue but it returns **false** in the case that the process start time isn't equal to the current time
     * (this is in case of adding processes using a vector, doesn't work if a process is added in a wrong timestep alone, no buffer).
     *
     * @param newProcess pointer to the new process
     * @return true if the process is added successfully, false otherwise
     */
    bool add_process(Process *newProcess);

    /**@brief Schedule the next time step
     *
     * @return PID of the scheduled process, -1 if no process is scheduled, -2 if all processes are finished
     */
    int schedule_next_time_step();

    /**@brief Calculate the average turnaround time
     *
     * @return average turnaround time
     */
    float get_turnaround_time();

    /**@brief Calculate the average waiting time
     *
     * @return average waiting time
     */
    float get_waiting_time();
};


#endif //OS_PROJECT_PRIORITYPREEMPTIVE_H