#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../businessLogic/calculatorFacade.h"
#include <QMainWindow>
#include <functional>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
private:
    Ui::MainWindow* ui;
    CalculatorFacade facade;
private:
    void run(std::function<void()> action);
    void updateDisplay();
    void connectButtons();
    void bind(QPushButton* button, std::function<void()> action);
};

#endif // MAINWINDOW_H
