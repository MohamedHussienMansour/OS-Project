#include <iostream>
using namespace std;
#include <algorithm>
#include <chrono>
#include <thread>
#include <string>
#include <cctype>
#include <vector>
#include "project.h"

int global_time = 0;


process::process(int burst_time = 0, int priority = 5, int arrival_time = 0, int waiting_time = 0, int finish_time = 0) {
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
    void process::decrement(int quanta=1) {
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
    int process::burst_time_now() {
        return copy_burst_time;
    };
    void process::calculate_waiting_time() {
     
        this->waiting_time = finish_time - arrival_time -burst_time;
      
    }
    void process::calculate_turn_time() {
    
        this->turn_around_time = finish_time-arrival_time;
    
    }


    scheduler::scheduler(string name) {
        type = name;
        global_time = 0;
    }
    void scheduler::add_process( int burst_time , int priority=5) {
        process p1( burst_time, priority,global_time);
        ready_queue.push_back(p1);
        burst_time_table.push_back({ p1.id ,p1.arrival_time , p1.copy_burst_time });
      
    }
    void scheduler::sort_priority_for_ready_queue() {
        std::sort(ready_queue.begin(), ready_queue.end(), [](const process& p1, const process& p2) {
            return p1.priority > p2.priority;
        });
    }
    void scheduler::sort_burst_for_ready_queue() {
        std::sort(ready_queue.begin(), ready_queue.end(), [](const process& p1, const process& p2) {
            return p1.copy_burst_time < p2.copy_burst_time;
        });
    }
    void scheduler::adding_process_dynamically(string name, int burst_time, int priority = 5) {
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
    vector<process> scheduler::get_ready_queue() {
        return ready_queue;
    }
    float scheduler::calculate_average_waiting_time() {
        float averagee = 0;
        for (process u : ready_queue) {
           
            averagee += u.waiting_time;
        }
        return averagee / ready_queue.size();
    }
    float scheduler::calculate_average_turn_around_time() {
        float averagee = 0;
        for (process u : ready_queue) {
          
            averagee += u.turn_around_time;
        }
        return averagee / ready_queue.size();
    }
    string scheduler::to_lower_string(string s) {
        for (auto& c : s) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        return s;
    }
    
    void scheduler::build_table_processes_info() {
        for (auto& u : ready_queue) {
            processes_info.push_back({ u.id,u.arrival_time , u.burst_time,u.waiting_time,u.turn_around_time });
        }
        show_table_processes_info();
    }
    void scheduler::show_table_processes_info() {
        
        for (auto & u : processes_info) {
            cout <<'p' << u[0] << "\t" << u[1] << "\t" << u[2] << "\t" << u[3] << "\t" << u[4] << endl;
           
        }
    }
    void scheduler::show_burst_time_table() {
        
        for (auto & u : burst_time_table) {
            cout << 'p' << u[0] << "\t" << u[1] << "\t" << u[2] << endl;
            
        }
    }
    void scheduler::modify_table_burst_time(int pos , int modifiy_to) {
        burst_time_table[pos][1] = modifiy_to;

    }
