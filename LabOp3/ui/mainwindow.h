#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "../logic/appContext.h"
#include "../ui/graphWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableWidget* table;
    GraphWindow* graph;

    AppContext context;

    void on_loadDataPushButton_clicked();
    void on_getFilePushButton_clicked();
    void addDataTable();
    void on_calculatePushButton_clicked();
    void errorsHandle(StatusCode);
    void resetApp();
    void resetWindow();
    void freeContext(AppContext*);
};
#endif // MAINWINDOW_H
