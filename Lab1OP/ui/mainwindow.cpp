#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../entryPoint.h"
#include "../constants.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startSystemBox->addItem("10", 10);
    ui->startSystemBox->addItem("8", 8);
    ui->startSystemBox->addItem("2", 2);

    for (int i = 0; i < ui->startSystemBox->count(); i++)
        ui->startSystemBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);

    ui->endSystemBox->addItem("2", 2);
    ui->endSystemBox->addItem("8", 8);
    ui->endSystemBox->addItem("10", 10);

    for (int i = 0; i < ui->startSystemBox->count(); i++)
        ui->endSystemBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);

    connect(ui->convertorPushButton, &QPushButton::clicked, this, &MainWindow::on_convertorPushButton_clicked);
    connect(ui->swaperNumSystem, &QPushButton::clicked, this, &MainWindow::on_swaperNumSystem_clicked);
    doOperation(INITIALIZATION, &context, NULL);
    updateLabelsUserValue();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_convertorPushButton_clicked() {
    AppParams params;
    QByteArray bytes = ui->userValueEdit->text().toUtf8();
    strncpy(params.strUserValue, bytes.constData(), SIZE_ARRAY_SYMBOL - 1);
    params.startNumSystem = ui->startSystemBox->currentData().toInt();
    params.endNumSystem = ui->endSystemBox->currentData().toInt();

    doOperation(VALIDATION, &context, &params);

    if (!context.flagError) {
        doOperation(CONVERTION, &context, &params);
        updateLabelsConvert();
    } else {
        QMessageBox::warning(this, "", context.errorPrint);
        doOperation(INITIALIZATION, &context, NULL);
        updateLabelsUserValue();
    }
}

void MainWindow::updateLabelsConvert() {
    ui->convertValueField->setText(context.strConvertedNumber);
}

void MainWindow::updateLabelsUserValue() {
    ui->userValueEdit->setText(context.strConvertedNumber);
    ui->convertValueField->setText(DEFAULT_FIELD);
}

void MainWindow::on_swaperNumSystem_clicked() {
    AppParams params;
    params.startNumSystem = ui->startSystemBox->currentData().toInt();
    params.endNumSystem = ui->endSystemBox->currentData().toInt();
    QByteArray bytes = ui->userValueEdit->text().toUtf8();
    strncpy(params.strUserValue, bytes.constData(), SIZE_ARRAY_SYMBOL - 1);

    doOperation(SWAP, &context, &params);
    updateLabelsSwaper(&params);


    ui->startSystemBox->setCurrentIndex(ui->startSystemBox->findData(params.startNumSystem));
    ui->endSystemBox->setCurrentIndex(ui->endSystemBox->findData(params.endNumSystem));
}

void MainWindow::updateLabelsSwaper(AppParams* params) {
    ui->userValueEdit->setText(params->strUserValue);
    ui->convertValueField->setText(context.strConvertedNumber);
}






