//
// Created by Ahmed Hussein on 4/9/2025.
//

#ifndef OS_PROJECT_PROCESS_H
#define OS_PROJECT_PROCESS_H


class Process {
private:
    // Process attributes
    int startTime;
    int endTime;
    int priority;
    int pid;
    int burstTime;
    int remainingBurstTime;

    static int processCounter; // Static variable to keep track of process IDs
public:

    /**@brief Constructor for the Process class
     *
     * @param startTime
     * @param priority
     * @param burstTime
     */
    Process(int startTime, int priority, int burstTime);

    /**@brief calculate the turnaround time
     *
     * @return turnaround time
     */
    int get_turnaround_time();

    /**@brief calculate the waiting time
     *
     *
     * @return waiting time
     */
    int get_waiting_time();

    // setters
    void set_end_time(int endTime);
    void set_burst_time(int burstTime);
    void set_remaining_burst_time(int remainingBurstTime);

    // getters
    int get_remaining_burst_time();
    int get_burst_time();
    int get_start_time();
    int get_priority();
    int get_pid();


};


#endif //OS_PROJECT_PROCESS_H
