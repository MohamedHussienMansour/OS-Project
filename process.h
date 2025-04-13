class process {
public:
    int pid;
    int burst_time;
    int waiting_time;
    int arrival_time;
    int finish_time;
    int turn_around_time;
    int priority;
    int copy_burst_time;
    process(int pid, int arrival_time = 0 , int burst_time = 0, int priority = 5) {
        this->pid=pid;
        this->priority = priority;
        this->burst_time = burst_time;
        this->waiting_time = 0;
        this->arrival_time = arrival_time;
        this->finish_time = 0;
        copy_burst_time = burst_time;
        turn_around_time = 0;
    }

    int burst_time_now() {
        return copy_burst_time;
    };
    void calculate_waiting_time() {
        this->waiting_time = finish_time - arrival_time -copy_burst_time;
    }
    void calculate_turn_time() {
        this->turn_around_time = finish_time-arrival_time;
    }
    
};