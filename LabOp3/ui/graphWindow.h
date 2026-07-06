#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QPainter>

#include "../logic/appContext.h"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void setMetric(const AppContext*);
    void clearGraph();
    ~GraphWindow();

private:
    Ui::GraphWindow *ui;

    int highOY;
    int dataHighOY;
    int rightOX;
    int startOX;
    int startOY;
    int stepOX;
    double axisMin;
    double axisMax;
    Metrics metrics;
    double* valuesMetric = NULL;

    void paintAxis(QPainter*);
    void paintDesignation(QPainter*);
    void paintValues(QPainter*);
    int getPixelOY(double);
    int getPixelOX(int);
};

#endif // GRAPHWINDOW_H
