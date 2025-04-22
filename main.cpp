#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTimer>
#include <QHeaderView>
#include <QMessageBox>
#include <qgraphicsitem.h>
#include <QThread>
#include "simulationworker.h"
#include "process.h"
#include "priority_non.h"
#include "gantt_chart_window.h"
using namespace std;

vector<process> myprocesses;
int currentXPosition = 0;
// Main GUI
class SchedulerGUI : public QMainWindow {
    Q_OBJECT

public:
    SchedulerGUI(QWidget *parent = nullptr) : QMainWindow(parent), ganttWindow(nullptr) {
        QWidget *central = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(central);

        // Scheduler Settings
        QGroupBox *settingsBox = new QGroupBox("Scheduler Settings");
        QHBoxLayout *settingsLayout = new QHBoxLayout(settingsBox);

        resize(1000,700);

        schedulerType = new QComboBox();
        schedulerType->addItems({"FCFS", "SJF Preemptive", "SJF Non-Preemptive", "Priority Preemptive", "Priority Non-Preemptive", "Round Robin"});
        quantumLabel = new QLabel("Quantum:");
        quantum = new QSpinBox();
        quantum->setMinimum(1);
        quantum->setMaximum(100);
        quantumLabel->hide();
        quantum->hide();

        connect(schedulerType, &QComboBox::currentTextChanged, this, &SchedulerGUI::onSchedulerChanged);

        checkLiveMode = new QCheckBox("Live Mode");
        btnStart = new QPushButton("Start");
        btnReset = new QPushButton("Reset");

        connect(btnStart, &QPushButton::clicked, this, &SchedulerGUI::startSimulation);
        connect(btnReset, &QPushButton::clicked, this, &SchedulerGUI::resetSimulation);


        settingsLayout->addWidget(new QLabel("Scheduler:"));
        settingsLayout->addWidget(schedulerType);
        settingsLayout->addWidget(quantumLabel);
        settingsLayout->addWidget(quantum);
        settingsLayout->addWidget(checkLiveMode);
        settingsLayout->addWidget(btnStart);
        settingsLayout->addWidget(btnReset);

        // Add Process Section
        QGroupBox *addBox = new QGroupBox("Add Process");
        QHBoxLayout *addLayout = new QHBoxLayout(addBox);
        addLayout->setSpacing(120); // spacing between each pair
        pid = new QSpinBox(); pid->setMinimum(1);
        pid->setReadOnly(true);
        arrival = new QSpinBox(); arrival->setMinimum(0);
        burst = new QSpinBox(); burst->setMinimum(1);
        priority = new QSpinBox(); priority->setMinimum(0);
        priority->hide();
        priorityLabel = new QLabel("Priority:");
        priorityLabel->hide();

        btnAddProcess = new QPushButton("Add Process");
        connect(btnAddProcess, &QPushButton::clicked, this, &SchedulerGUI::addProcess);

        auto tightPair = [](QLabel * Label, QSpinBox *spinBox) {
            QWidget *pairWidget = new QWidget();
            QHBoxLayout *pairLayout = new QHBoxLayout(pairWidget);
            pairLayout->setContentsMargins(0, 0, 0, 0); // remove padding
            pairLayout->setSpacing(3); // very tight between label and input
            pairLayout->addWidget(Label);
            pairLayout->addWidget(spinBox);
            return pairWidget;
        };

        addLayout->addWidget(tightPair(new QLabel("PID:"), pid));
        addLayout->addWidget(tightPair(new QLabel("Arrival:"), arrival));
        addLayout->addWidget(tightPair(new QLabel("Burst:"), burst));
        addLayout->addWidget(tightPair(priorityLabel, priority));
        addLayout->addWidget(btnAddProcess);

        // Process Table
        processTable = new QTableWidget();
        processTable->setColumnCount(5);
        processTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Priority", "Remaining"});
        processTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        processTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Stats Labels
        avgWT = new QLabel("Avg Waiting Time: 0");
        avgTAT = new QLabel("Avg Turnaround Time: 0");

        // Add all to main layout
        mainLayout->addWidget(settingsBox);
        mainLayout->addWidget(addBox);
        mainLayout->addWidget(processTable);


        setCentralWidget(central);
        setWindowTitle("CPU Scheduler Simulator");
    }

private slots:
    void onSchedulerChanged(const QString &type) {
        bool isRR = (type == "Round Robin");
        bool isPriority = (type == "Priority Preemptive" || type == "Priority Non-Preemptive");
        quantumLabel->setVisible(isRR);
        quantum->setVisible(isRR);
        priority->setVisible(isPriority);
        priorityLabel->setVisible(isPriority);
    }

    void startSimulation() {
        ganttWindow = new GanttChartWindow(this);
        ganttWindow->show();
        ganttWindow->raise();
        ganttWindow->activateWindow();

        ganttWindow->scene()->clear();

        resetBurstTime();
        myprocesses.reserve(1000);
        currentXPosition = 0;
        bool liveMode = checkLiveMode->isChecked();
        QString selectedAlgorithm = schedulerType->currentText();

        // Create the thread and worker
        thread = new QThread;
        worker = new SimulationWorker(myprocesses, selectedAlgorithm, liveMode, arrival, quantum->value());
        worker->moveToThread(thread);

        // Connect signals and slots
        connect(thread, &QThread::started, worker, &SimulationWorker::run);
        connect(worker, &SimulationWorker::processReady, this, [=](int pid) {
            if (pid == -1)
                addToGanttChart(0);
            else{
                addToGanttChart(pid);

                int current_remaining=processTable->item(pid-1,4)->text().toInt();
                processTable->item(pid-1,4)->setText(QString::number(current_remaining-1));
            }
        });

        // Cleanup when done
        connect(ganttWindow, &GanttChartWindow::stopRequested, worker, &SimulationWorker::requestStop, Qt::DirectConnection);
        connect(worker, &SimulationWorker::finished, thread, &QThread::quit);
        connect(worker, &SimulationWorker::finished, worker, &QObject::deleteLater);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        connect(worker, &SimulationWorker::finished, this, &SchedulerGUI::onSimulationComplete);

        // Start it
        thread->start();

    }
    void resetSimulation() {
        // Clear table
        processTable->setRowCount(0);

        // Reset spin boxes
        pid->setValue(0);
        arrival->setValue(0);
        burst->setValue(1);
        priority->setValue(0);

        myprocesses.clear();

        // Reset stats
        avgWT->setText("Avg Waiting Time: 0");
        avgTAT->setText("Avg Turnaround Time: 0");

        // Close Gantt chart window if open
    }
    void addProcess() {
        int row = processTable->rowCount();
        processTable->insertRow(row);

        // Read values from input fields
        int p_pid = pid->value();
        int p_arrival = arrival->value();
        int p_burst = burst->value();
        int p_priority = priority->isVisible() ? priority->value() : 0; // only if visible

        // Fill the row
        auto centeredItem = [](int value) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(value));
            item->setTextAlignment(Qt::AlignCenter);
            return item;
        };

        processTable->setItem(row, 0, centeredItem(p_pid));
        processTable->setItem(row, 1, centeredItem(p_arrival));
        processTable->setItem(row, 2, centeredItem(p_burst));
        processTable->setItem(row, 3, centeredItem(p_priority));
        processTable->setItem(row, 4, centeredItem(p_burst)); // remaining = burstt

        myprocesses.push_back(process(p_pid,p_arrival,p_burst,p_priority));

        // Optionally, auto-increment PID
        pid->setValue(p_pid + 1);
    }
    // In SchedulerGUI class or wherever you want the function

    void addToGanttChart(int processId = 0) {
        if (!ganttWindow) {
            ganttWindow = new GanttChartWindow(this);
            ganttWindow->show();
        }

        // Ensure that the first process starts at position 0
        int rectWidth = 50;  // Rectangle width
        int rectHeight = 30; // Rectangle height

        // Create a rectangle representing the process, positioned sequentially
        QGraphicsRectItem *processRect = new QGraphicsRectItem(currentXPosition, 50, rectWidth, rectHeight);
        processRect->setBrush(QBrush(Qt::white));  // Set color for the process

        // Create text to show the process ID, centered within the rectangle
        QGraphicsTextItem *processText;
        if(processId==0) processText = new QGraphicsTextItem("idle");
        else processText = new QGraphicsTextItem(QString::number(processId));
        processText->setDefaultTextColor(Qt::black);

        // Adjust text position to center it inside the rectangle
        processText->setPos(currentXPosition + (rectWidth - processText->boundingRect().width()) / 2,
                            50 + (rectHeight - processText->boundingRect().height()) / 2);

        // Add the process rectangle and text to the scene
        if(ganttWindow==nullptr || ganttWindow->scene()==nullptr) return;
        ganttWindow->scene()->addItem(processRect);
        ganttWindow->scene()->addItem(processText);

        // Update the xPosition for the next process (move by the width of the rectangle)
        currentXPosition += rectWidth;  // This moves the next rectangle to the right
    }
    void resetBurstTime(){
        int n=myprocesses.size();
        for (int i = 0; i < n; ++i) {
            myprocesses[i].burst_time=myprocesses[i].copy_burst_time;
            processTable->item(i,4)->setText(QString::number(myprocesses[i].burst_time));
        }
    }
    void onSimulationComplete(){
        double avgWT = calculate_average_waiting_time();
        double avgTAT = calculate_average_turn_around_time();


        // Optional: Show message box
        QMessageBox::information(this, "Simulation Complete",
                                 QString("Avg Waiting Time: %1\nAvg Turnaround Time: %2")
                                     .arg(avgWT).arg(avgTAT));
    }

    float calculate_average_waiting_time() {
        float averagee = 0;
        for (process u : myprocesses) {

            averagee += u.waiting_time;
        }
        return averagee / myprocesses.size();
    }
    float calculate_average_turn_around_time() {
        float averagee = 0;
        for (process u : myprocesses) {

            averagee += u.turn_around_time;
        }
        return averagee / myprocesses.size();
    }




private:
    QComboBox *schedulerType;
    QLabel *quantumLabel;
    QLabel *priorityLabel;
    QSpinBox *quantum;
    QCheckBox *checkLiveMode;
    QPushButton *btnStart, *btnReset;

    QSpinBox *pid, *arrival, *burst, *priority;
    QPushButton *btnAddProcess;

    QTableWidget *processTable;
    QLabel *avgWT, *avgTAT;

    GanttChartWindow *ganttWindow = new GanttChartWindow(this);
    SimulationWorker* worker = nullptr;
    QThread* thread = nullptr;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SchedulerGUI gui;
    gui.show();
    return app.exec();
}
