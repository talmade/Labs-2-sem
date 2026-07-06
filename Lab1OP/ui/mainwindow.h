#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../logic/appContext.h"
#include "../logic/appParams.h"

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    AppContext context;

    void on_convertorPushButton_clicked();
    void on_swaperNumSystem_clicked();
    void updateLabelsUserValue();
    void updateLabelsConvert();
    void updateLabelsSwaper(AppParams*);
};
#endif // MAINWINDOW_H
