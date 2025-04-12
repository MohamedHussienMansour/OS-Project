#include <iostream>
#include <vector>
#include <algorithm>
#include "process.h"
using namespace std;


class priority_non{
    public:
        vector<process> &processes;
        vector<process*> waiting;
        int time;
        bool is_busy;
        process *curr_process;

        priority_non(vector<process> &processes_ref):processes(processes_ref){
            time=0;
            is_busy=false;
        }

        bool all_finished(){
            int n=processes.size();
            for (int i = 0; i < n; i++)
            {
                if(processes[i].burst_time!=0) return false;
            }
            return true;
        }

        static bool priority_sorting(process * p1,process * p2){
            return p1->priority>p2->priority;
        }

        int get_process(){
            if (all_finished())
            {
                return -2;
            }
            
            int n=processes.size();
            for (int i = 0; i < n; i++)
            {
                if(time==processes[i].arrival_time) waiting.push_back(&processes[i]); //checks if new process has arrived
            }

            time++;
            if(!is_busy){
                sort(waiting.begin(),waiting.end(),priority_non::priority_sorting); //sorting waiting queue according to priority
                if(!waiting.empty()){
                    is_busy=true;
                    curr_process = waiting.back();
                    waiting.pop_back();
                    curr_process->burst_time--;
                    if(curr_process->burst_time==0){
                        is_busy=false;
                        curr_process->finish_time=time;
                        curr_process->calculate_turn_time();
                        curr_process->calculate_waiting_time();
                    }
                    return curr_process->pid;
                }
                else{
                    return -1;
                }
            }
            else{
                curr_process->burst_time--;
                if(curr_process->burst_time==0){
                    is_busy=false;
                    curr_process->finish_time=time;
                    curr_process->calculate_turn_time();
                    curr_process->calculate_waiting_time();
                }
                return curr_process->pid;
            }
            return -1;
        }

};


int main(){
    vector<process> p = {process(1,0,3,2),process(2,2,6,1),process(3,5,1,3),process(4,9,2,2),process(5,12,4,2)};
    priority_non p1(p);
    int temp=0;
    while (temp!=-2)
    {
        temp=p1.get_process();
        if(temp==-2) continue;
        cout<<temp<<endl;
    }

    for (int i = 0; i < p.size(); i++)
    {
        cout<<p[i].waiting_time<<" - ";
    }
        for (int i = 0; i < p.size(); i++)
    {
        cout<<p[i].turn_around_time<<" - ";
    }
}