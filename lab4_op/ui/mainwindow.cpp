#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QVBoxLayout>
#include <math.h>

#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "../entryPoint.h"

#define DEGREES_TO_RADIANS (M_PI / 180.0)
#define SCALE_FACTOR 100.0

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    doOperations(INITIALIZATION, &context);

    surfaceWidget = new SurfaceWidget(ui->wireframeWidget);
    QVBoxLayout* layout = new QVBoxLayout(ui->wireframeWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(surfaceWidget);

    connect(ui->selectFileButton, &QPushButton::clicked, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->normalizeButton, &QPushButton::clicked, this, &MainWindow::on_normalizeButton_clicked);
    connect(ui->rotateXSlider, &QSlider::valueChanged, this, &MainWindow::on_rotateXSlider_valueChanged);
    connect(ui->rotateYSlider, &QSlider::valueChanged, this, &MainWindow::on_rotateYSlider_valueChanged);
    connect(ui->rotateZSlider, &QSlider::valueChanged, this, &MainWindow::on_rotateZSlider_valueChanged);
    connect(ui->translateXSlider, &QSlider::valueChanged, this, &MainWindow::on_translateXSlider_valueChanged);
    connect(ui->translateYSlider, &QSlider::valueChanged, this, &MainWindow::on_translateYSlider_valueChanged);
    connect(ui->translateZSlider, &QSlider::valueChanged, this, &MainWindow::on_translateZSlider_valueChanged);
    connect(ui->scaleSlider, &QSlider::valueChanged, this, &MainWindow::on_scaleSlider_valueChanged);
}

void MainWindow::showError() {
    QMessageBox::critical(this, "Error", context.errorMessage);
}

void MainWindow::updateSurface() {
    doOperations(TRANSFORMATION, &context);
    if (context.status != NO_ERROR)
        showError();
    else
        surfaceWidget->render(&context);
}

void MainWindow::on_selectFileButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(
        this, "Select CSV file", "", "CSV Files (*.csv)");

    if (!filename.isEmpty()) {
        doOperations(CLEARING, &context);
        doOperations(INITIALIZATION, &context);

        QByteArray utf8 = filename.toUtf8();
        strncpy(context.filename, utf8.constData(), strlen(utf8.constData()) + 1);

        doOperations(UPLOADING_FILE, &context);
        if (context.status != NO_ERROR)
            showError();
        else {
            QFileInfo fileInfo(filename);
            ui->filePathEdit->setText(fileInfo.fileName());
        }
    }
}

void MainWindow::on_normalizeButton_clicked() {
    context.scene.normMin = ui->normMinSpinBox->value();
    context.scene.normMax = ui->normMaxSpinBox->value();
    context.scene.step = ui->stepSpinBox->value();

    doOperations(NORMALIZATION, &context);
    if (context.status != NO_ERROR)
        showError();
    else
        updateSurface();
}

void MainWindow::on_rotateXSlider_valueChanged(int value) {
    context.transform.rotateX = value * DEGREES_TO_RADIANS;
    updateSurface();
}

void MainWindow::on_rotateYSlider_valueChanged(int value) {
    context.transform.rotateY = value * DEGREES_TO_RADIANS;
    updateSurface();
}

void MainWindow::on_rotateZSlider_valueChanged(int value) {
    context.transform.rotateZ = value * DEGREES_TO_RADIANS;
    updateSurface();
}

void MainWindow::on_translateXSlider_valueChanged(int value) {
    context.transform.translateX = value;
    updateSurface();
}

void MainWindow::on_translateYSlider_valueChanged(int value) {
    context.transform.translateY = value;
    updateSurface();
}

void MainWindow::on_translateZSlider_valueChanged(int value) {
    context.transform.translateZ = value;
    updateSurface();
}

void MainWindow::on_scaleSlider_valueChanged(int value) {
    context.transform.scale = value / SCALE_FACTOR;
    updateSurface();
}

MainWindow::~MainWindow() {
    doOperations(CLEARING, &context);
    delete ui;
}
