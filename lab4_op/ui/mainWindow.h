#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "surfaceWidget.h"
#include "../logic/appContext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow* ui;
    AppContext context;
    SurfaceWidget* surfaceWidget;
private:
    void showError();
    void updateSurface();
private:
    void on_selectFileButton_clicked();
    void on_stepSpinBox_valueChanged(double arg1);
    void on_normMinSpinBox_valueChanged(double arg1);
    void on_normMaxSpinBox_valueChanged(double arg1);
    void on_normalizeButton_clicked();
    void on_rotateXSlider_valueChanged(int value);
    void on_rotateYSlider_valueChanged(int value);
    void on_rotateZSlider_valueChanged(int value);
    void on_translateXSlider_valueChanged(int value);
    void on_translateYSlider_valueChanged(int value);
    void on_translateZSlider_valueChanged(int value);
    void on_scaleSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H
