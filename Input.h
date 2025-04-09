#include<string>
using namespace std;
class process{
public:
    string name;
    static int pid;
    int burst_time;
    int waiting_time;
    int arrival_time;
    int finish_time;
    int turn_around_time;
    int priority;
    int id;
    int copy_burst_time;
    process(int burst_time = 0, int arrival_time = 0, int priority = 5, int waiting_time = 0, int finish_time = 0) {
        id = pid;
        this->name = string("p")+ to_string(id);
        this->priority = priority;
        this->burst_time = burst_time;
        this->waiting_time = waiting_time;
        this->arrival_time = arrival_time;
        this->finish_time = finish_time;
        copy_burst_time = burst_time;
        turn_around_time = 0;
        pid++;
    };
};


int process::pid = 0;
