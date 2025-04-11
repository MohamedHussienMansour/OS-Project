#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
using namespace std;
#include <algorithm>
#include <chrono>
#include <thread>
#include <string>
#include <cctype>
#include <vector>


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
    process(int, int, int, int, int);
    void decrement(int);
    int burst_time_now();
    void calculate_waiting_time();
    void calculate_turn_time();

};

class scheduler {
public:
    string type; //sjf preemptive , sjf non preemptive,fcfs , priority preemptive  , priority  non preemptive 
    vector<process> ready_queue;
    vector<vector<int>> burst_time_table;
    vector<vector<int>> processes_info;

    scheduler(string name);
    void add_process(int, int);
    void sort_priority_for_ready_queue();
    void sort_burst_for_ready_queue();
    void adding_process_dynamically(string, int, int);
    vector<process> get_ready_queue();
    float calculate_average_waiting_time();
    float calculate_average_turn_around_time();
    string to_lower_string(string s);
    void build_table_processes_info();
    void show_table_processes_info();
    void show_burst_time_table();
    void modify_table_burst_time(int, int);

};

#endif
