#include <iostream>
using namespace std;
#include <algorithm>
#include <chrono>
#include <thread>
#include <string>
#include <cctype>
#include <vector>

int global_time = 0;

class process {
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
    process(int burst_time = 0, int priority = 5, int arrival_time = 0, int waiting_time = 0, int finish_time = 0) {
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
    void decrement(int quanta=1) {
        cout << name;
        while (quanta > 0) {
            
            if (copy_burst_time > 0) {
                // for simulation purpose as if it waiting 4 second on the showing screen 
                cout << "|";
                using namespace std::chrono;
                auto start = steady_clock::now();
                auto duration = seconds(1);
                while (((steady_clock::now()) - start) < duration) {
                    cout << ".";
                    std::this_thread::sleep_for(milliseconds(300));
                }
                cout << "|";
                // till here the simulation purspose 
                quanta--;
                copy_burst_time--;
                global_time++;
            }
            else {
                
                finish_time = global_time;
                calculate_waiting_time();
                calculate_turn_time();
                break;
            }
        }
        if (copy_burst_time <= 0) {
         
            this->finish_time = global_time;
          
            calculate_waiting_time();
            calculate_turn_time();
        }
        
    }
    int burst_time_now() {
        return copy_burst_time;
    };
    void calculate_waiting_time() {
     
        this->waiting_time = finish_time - arrival_time -burst_time;
      
    }
    void calculate_turn_time() {
    
        this->turn_around_time = finish_time-arrival_time;
    
    }
    
};

class scheduler {
public:
    string type; //sjf preemptive , sjf non preemptive,fcfs , priority preemptive  , priority  non preemptive 
    vector<process> ready_queue;
    vector<vector<int>> burst_time_table;
    vector<vector<int>> processes_info;
    
    scheduler(string name) {
        type = name;
        global_time = 0;
    }
    void add_process( int burst_time , int priority=5) {
        process p1( burst_time, priority,global_time);
        ready_queue.push_back(p1);
        burst_time_table.push_back({ p1.id ,p1.arrival_time , p1.copy_burst_time });
      
    }
    void sort_priority_for_ready_queue() {
        std::sort(ready_queue.begin(), ready_queue.end(), [](const process& p1, const process& p2) {
            return p1.priority > p2.priority;
        });
    }
    void sort_burst_for_ready_queue() {
        std::sort(ready_queue.begin(), ready_queue.end(), [](const process& p1, const process& p2) {
            return p1.copy_burst_time < p2.copy_burst_time;
        });
    }
    void adding_process_dynamically(string name, int burst_time, int priority = 5) {
        process p1( burst_time, priority, global_time);
        ready_queue.push_back(p1);
        burst_time_table.push_back({ p1.arrival_time , p1.copy_burst_time });
        // msh mot2kd mnha awi alli t7t bs mogrd tfkir mbd2i
        if (to_lower_string(type) == "sjf preemptive" || to_lower_string(type) == "sjf non preemptive") {
            sort_burst_for_ready_queue();
        }
        if (to_lower_string(type) == "priority preemptive" || to_lower_string(type) == "priority  non preemptive") {
            sort_priority_for_ready_queue();
        }
    }
    vector<process> get_ready_queue() {
        return ready_queue;
    }
    float calculate_average_waiting_time() {
        float averagee = 0;
        for (process u : ready_queue) {
           
            averagee += u.waiting_time;
        }
        return averagee / ready_queue.size();
    }
    float calculate_average_turn_around_time() {
        float averagee = 0;
        for (process u : ready_queue) {
          
            averagee += u.turn_around_time;
        }
        return averagee / ready_queue.size();
    }
    string to_lower_string(string s) {
        for (auto& c : s) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return s;
    }
    
    void build_table_processes_info() {
        for (auto& u : ready_queue) {
            processes_info.push_back({ u.id,u.arrival_time , u.burst_time,u.waiting_time,u.turn_around_time });
        }
        show_table_processes_info();
    }
    void show_table_processes_info() {
        
        for (auto & u : processes_info) {
            cout <<'p' << u[0] << "\t" << u[1] << "\t" << u[2] << "\t" << u[3] << "\t" << u[4] << endl;
           
        }
    }
    void show_burst_time_table() {
        
        for (auto & u : burst_time_table) {
            cout << 'p' << u[0] << "\t" << u[1] << "\t" << u[2] << endl;
            
        }
    }
    void modify_table_burst_time(int pos , int modifiy_to) {
        burst_time_table[pos][1] = modifiy_to;

    }
 
};
/*
fi mo4kla an processes lw 0 lw at3mlha sorting tani htzhr fi grant chart f lazm alli bi3ml scheduling y3ml check lw finish time msh b 0 m3na an function 5lst 
aw copy_burst_time akbr mn 0 s3tha yd5lha fi grant chartt 8ir kda dih process 5lst 
*/
int process::pid = 0;
int main()
{
    string type;
    
    cout << "            scheduler project            " << endl;;
    cout << "the scheduler types avaliable are:" ;;
    cout << "sjf preemptive , sjf non preemptive,fcfs , priority preemptive  , priority  non preemptive" << endl;
    cout << "please enter the type of schduler you want: " ;
    getline(cin,type);
    scheduler sched(type);
    cout << endl<<"please enter number of processes you want: ";
    int number_of_processes;
    cin >> number_of_processes;
    int burst_size;
    for (int i = 0; i < number_of_processes; i++) {
        cout << endl<<"please enter the burst size of "<<"p" << to_string(i) << ": ";
        cin >> burst_size;
        sched.add_process(burst_size);
    }
    // Sort the ready queue by burst time (SJF Non-Preemptive)
    sched.sort_burst_for_ready_queue();

    for (auto & p : sched.ready_queue) {
        p.decrement(p.burst_time); // run the whole burst time
       
    }
   

    // Show process info table
    sched.build_table_processes_info();

    // Print average times
    cout << "\nAverage Waiting Time: " << sched.calculate_average_waiting_time() << endl;
    cout << "Average Turnaround Time: " << sched.calculate_average_turn_around_time() << endl;
    ;
}

