using namespace std;

#include "fcfs.h"
#include <iostream>
#include <vector>
int main()
{
    vector<process> p1;
    
    p1.push_back(process(1,0,3,0));
    p1.push_back(process(2,3,2,0));
    p1.push_back(process(3,1,4,0));
    p1.push_back(process(4,2,3,0));
    p1.push_back(process(6,7,1,2));
    FCFS f1(p1);
    int temp=0;
    int time=0;
    while (temp!=-2)
    {
        if(time==5) p1.push_back(process(5,10,4,0));
        temp=f1.get_process();
        cout<<"TimeStep "<<time<<": "<<temp<<endl;
        time++;
    }


    float avg_tat=0,avg_wt=0;
    for (int i = 0; i < p1.size(); i++)
    {
        avg_wt+=p1[i].waiting_time;
        avg_tat+=p1[i].turn_around_time;
    }

    cout<<"avg turn around = "<<avg_tat/p1.size()<<endl;
    cout<<"avg waiting = "<<avg_wt/p1.size()<<endl;
    
}

