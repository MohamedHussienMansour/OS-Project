using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include "project.h"

class SJFNonPreemptive {
public:
    vector<process> initialProcesses;
    vector<process> readyQueue;
    process* currentProcess;
    int currentTime;
    vector<process> completedProcesses;
    vector<process> newlyAddedProcesses;

    SJFNonPreemptive() {
        currentTime = 0;
        currentProcess = nullptr;
    }

    void addInitialProcess(process p) {
        initialProcesses.push_back(p);
    }

    void initialRun();
    void setCurrent();
    int returnCurrent();

};

void SJFNonPreemptive::initialRun() {
    currentTime = 0;
    readyQueue.clear();
    completedProcesses.clear();

    //add intial processes to ready queue
    for (const auto& p : initialProcesses) {
        readyQueue.push_back(p);
    }
    initialProcesses.clear();
}

void SJFNonPreemptive::setCurrent() {
    //sets current process
    if (currentProcess == nullptr && !readyQueue.empty()) {
        //sort ready queue by burst time
        sort(readyQueue.begin(), readyQueue.end(), [](const process& a, const process& b) {
            return a.burst_time < b.burst_time;
            });

        currentProcess = new process(readyQueue.front()); //gets first process
        readyQueue.erase(readyQueue.begin());   //remove first process from ready queue
    }
}


int SJFNonPreemptive::returnCurrent() {
    setCurrent(); // Select the next process if none is running

    if (currentProcess != nullptr) {
        if (currentProcess->copy_burst_time > 0) {  //if process still has burst time remaining
            currentProcess->copy_burst_time--;
            cout << "Time: " << currentTime << " process: " << currentProcess->name << " (remaining burst time: " << currentProcess->copy_burst_time << ")" << endl;
            currentTime++;
            return currentProcess->id;
        }
        else if (currentProcess->copy_burst_time == 0) {    //if process is done executing
            //calculate its waiting and turn around time
            currentProcess->finish_time = currentTime;
            currentProcess->calculate_waiting_time();
            currentProcess->calculate_turn_time();
            completedProcesses.push_back(*currentProcess);
            //delete it
            delete currentProcess;
            currentProcess = nullptr;
            //set a new process to run
            setCurrent();
            if (currentProcess != nullptr) {
                if (currentProcess->copy_burst_time > 0) {
                    currentProcess->copy_burst_time--;
                    cout << "Time: " << currentTime << " process: " << currentProcess->name << " (remaining burst time: " << currentProcess->copy_burst_time << ")" << endl;
                    currentTime++; 
                    return currentProcess->id;
                }
            }
        }
    }
    return -1; //return -1 when all processes finish (ready queue is empty)
}

//Testing
int process::pid = 0;
int main() {
    SJFNonPreemptive scheduler;
    int n = 3;      //number of processes
    int burstTime;
    float avgWT = 0;
    float avgTT = 0;

    cout << "Enter the burst time for 4 processes (all arriving at time 0):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> burstTime;
        scheduler.addInitialProcess(process(burstTime, 0, 0, 0, 0));
    }

    cout << "\n--- Running SJF Non-Preemptive Simulation ---" << endl;

    scheduler.initialRun();

    cout << "\n--- Simulation Timeline ---" << endl;

    while (scheduler.currentProcess != nullptr || !scheduler.readyQueue.empty()) {
        cout << "Returned value: " << scheduler.returnCurrent() << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // For visualization
    }

    cout << "\n--- Simulation Results ---" << endl;
    for (const auto& p : scheduler.completedProcesses) {
        cout << "Process " << p.name << ": Finish Time = " << p.finish_time
            << ", Waiting Time = " << p.waiting_time << ", Turnaround Time = " << p.turn_around_time << endl;
        avgWT += p.waiting_time;
        avgTT += p.turn_around_time;
    }
    cout << endl;
    avgWT = avgWT / n;
    avgTT = avgTT / n;
    cout << "Average waiting time = " << avgWT << endl;
    cout << "Average turn around time = " << avgTT << endl;

    return 0;
}


