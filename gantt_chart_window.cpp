#include "gantt_chart_window.h"

GanttChartWindow::GanttChartWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Gantt Chart");
    setMinimumSize(1200, 150);

    ganttScene = new QGraphicsScene(this);
    ganttView = new QGraphicsView(ganttScene);



    setCentralWidget(ganttView);
}

void GanttChartWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "GanttChartWindow hidden instead of closed";
    emit stopRequested();   // Tell whoever is listening to stop the simulation
}


QGraphicsScene* GanttChartWindow::scene() const {
    return ganttScene;
}
