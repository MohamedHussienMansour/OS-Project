#ifndef PROCESS
#define PROCESS

#include <iostream>
using namespace std;

class process 
{
    public:
        string name;
        int arrival;
        int burst;
        int priority;
        int finish;
        process(string name,int arrival,int burst,int priority=0){
            this->name=name;
            this->arrival=arrival;
            this->burst=burst;
            this->priority=priority;
        }    
};


#endif