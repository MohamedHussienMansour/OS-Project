#ifndef GANTT_CHART_WINDOW_H
#define GANTT_CHART_WINDOW_H
#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class GanttChartWindow : public QMainWindow {
    Q_OBJECT
public:
    GanttChartWindow(QWidget *parent = nullptr);
    QGraphicsScene* scene() const;
    void clean();

private:
    QGraphicsView *ganttView;
    QGraphicsScene *ganttScene;

signals:
    void stopRequested(); // emitted when the window is closed

protected:
    void closeEvent(QCloseEvent *event) override;  // <-- Override for close event
};


#endif // GANTT_CHART_WINDOW_H
