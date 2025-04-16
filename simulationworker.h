#pragma once

#include <QObject>
#include <vector>
#include "process.h"
#include <QSpinBox>

class SimulationWorker : public QObject {
    Q_OBJECT
public:
    SimulationWorker(std::vector<process> &processes, const QString& algorithmType, bool liveMode,QSpinBox *arrive, int quantum);
    void requestStop();

signals:
    void processReady(int pid);  // emit when a process is ready to show
    void finished();             // emit when simulation ends

public slots:
    void run();  // simulation logic lives here

private:
    std::vector<process> &myProcesses;
    std::atomic<bool> stopRequestedFlag = false;
    QString algorithm;
    bool isLive;
    int quant;
    QSpinBox *arrival;
};
