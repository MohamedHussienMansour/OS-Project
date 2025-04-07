#include <iostream>
#include <vector>
#include <algorithm>
#include "process.h"
#include "Grantt_chart.h"
using namespace std;



bool priority_sorting(process * p1,process * p2){
    return p1->priority>p2->priority;
}

grantt_chart priority_non(vector<process> processes,int n){
    vector<process*> waiting;
    vector<int> bursts;
    grantt_chart g;

    int time=0,total_time=0;

    //Calculating Total time
    for (int i = 0; i < n; i++)
    {
        total_time+=processes[i].burst;
        bursts.push_back(processes[i].burst);
    }

    //starting timeline
    while(time<total_time){
        for (int i = 0; i < n; i++)
        {
            if(time==processes[i].arrival) waiting.push_back(&processes[i]); //checks if new process has arrived
        }

        sort(waiting.begin(),waiting.end(),priority_sorting); //sorting waiting queue according to priority

        if(!waiting.empty()){
            process *current = waiting.back();
            waiting.pop_back();

            while (current->burst!=0)
            {
                g.chart.push_back(current->name);
                current->burst--;
                time++;
                for (int i = 0; i < n; i++)
                {
                    //checks if new process has arrived while current process is executed
                    if(time==processes[i].arrival) waiting.push_back(&processes[i]);
                }
            }        
            current->finish=time;
        }
        else{
            g.chart.push_back("no operation");
            time++;
        }
    }



    //Calculating TAT and WT
    float curr_turnaround;
    float curr_waiting;
    for (int i = 0; i < n; i++)
    {
        curr_turnaround = processes[i].finish-processes[i].arrival;
        curr_waiting = curr_turnaround - bursts[i];
        g.avg_turnaround += curr_turnaround;
        g.avg_waiting += curr_waiting;
    }
    g.avg_turnaround = g.avg_turnaround/n;
    g.avg_waiting = g.avg_waiting/n;
    

    return g;
    
}

int main(){

    vector<process> p = {process("p1",0,3,2),process("p2",2,6,1),process("p3",5,1,3),process("p4",9,2,2),process("p5",12,4,1)};
    
    grantt_chart g = priority_non(p,p.size());
    
    for (int i = 0; i < g.chart.size(); i++)
    {
        cout<<"time_unit "<<i<<": "<<g.chart[i]<<endl;
    }
    cout<<"AVG TURN_AROUND = "<<g.avg_turnaround<<endl;
    cout<<"AVG WAITING = "<<g.avg_waiting<<endl;
}