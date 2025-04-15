#include "simulationworker.h"
#include "priority_non.h"
#include "round_robin.h"
#include "priority_preemptive.h"
#include "sjf_preemptive.h"
#include "sjf_non.h"
#include "fcfs.h"
#include <thread>
#include <chrono>
#include <QDebug>

SimulationWorker::SimulationWorker(std::vector<process> &processes, const QString& algorithmType, bool liveMode, int quantam)
    : myProcesses(processes), algorithm(algorithmType), isLive(liveMode), quant(quantam) {}

void SimulationWorker::run() {
    if(algorithm=="Round Robin"){
        round_robin p1(myProcesses,quant);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
    else if(algorithm=="Priority Non-Preemptive"){
        priority_non p1(myProcesses);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(algorithm=="Priority Preemptive"){
        priority_preemptive p1(myProcesses);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(algorithm=="FCFS"){
        FCFS p1(myProcesses);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(algorithm=="SJF Preemptive"){
        sjf_preemptive p1(myProcesses);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else if(algorithm=="SJF Non-Preemptive"){
        sjf_non p1(myProcesses);
        int temp = 0;

        while (temp != -2 && !stopRequestedFlag) {
            temp = p1.get_process();

            if (temp == -2) continue;

            emit processReady(temp);  // send signal to main thread

            if(isLive) std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }


    emit finished();  // done!
}

void SimulationWorker::requestStop() {
    stopRequestedFlag = true;
    qDebug() <<"stop done";
}
