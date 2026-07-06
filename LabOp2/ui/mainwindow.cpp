#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../logic/stringMemory.h"
#include "../entryPoint/entryPoint.h"
#include "../logic/Iterator.h"
#include "../logic/constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dataTable->setColumnCount(COLUMN);

    QStringList headers;
    headers << "year" << "region" << "npg" << "birth_rate"
            << "death_rate" << "gdw" << "urbanization";

    ui->dataTable->setHorizontalHeaderLabels(headers);

    doOperation(INITIALIZATION, &context, NULL);

    connect(ui->getFilePushButton, &QPushButton::clicked, this, &MainWindow::on_getFilePushButton_clicked);
    connect(ui->loadDataPushButton, &QPushButton::clicked, this, &MainWindow::on_loadDataPushButton_clicked);
    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::on_calculatePushButton_clicked);
}

void MainWindow::on_getFilePushButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(
        this,
        "Выберите CSV файл",
        "",
        "CSV files (*.csv)"
        );

    if (!filename.isEmpty()) {
        strncpy(context.filename, filename.toUtf8().constData(), SIZE_BUFFER - 1);
        ui->FileEdit->setText(filename);
    } else {
        context.flagErrorCode = FILE_NOT_SELECT;
        resetApp();
    }
}

void MainWindow::on_loadDataPushButton_clicked() {
    if (strlen(context.filename) == 0)
        context.flagErrorCode = FILE_NOT_SELECT;

    if (context.list != NULL && context.flagErrorCode == SUCCESSFULLY) {
        freeList(context.list);
        context.lines.totalLines = 0;
        context.lines.successLines = 0;
        context.lines.errorLines = 0;
    }

    if (context.flagErrorCode == SUCCESSFULLY)
        doOperation(LOADING_DATA, &context, NULL);

    if (context.flagErrorCode == SUCCESSFULLY) {      
        QMessageBox::information(this, "Загрузка",
                                 QString("Всего строк: %1\nОшибок: %2\nУспешно: %3")
                                     .arg(context.lines.totalLines)
                                     .arg(context.lines.errorLines)
                                     .arg(context.lines.successLines));
    }

    if (context.flagErrorCode == SUCCESSFULLY) {
        addDataTable();
    } else
        resetApp();
}

void MainWindow::addDataTable() {
    Iterator iter = iteratorCreate(context.list);

    ui->dataTable->setRowCount(0);

    int row = 0;
    while(iteratorHasNext(&iter)) {
        TableParams* data = iteratorNext(&iter);

        QString regionFilter = ui->RepublicLineEdit->text();


        if (regionFilter.isEmpty() || QString(data->republic) == regionFilter) {
            ui->dataTable->insertRow(row);

            ui->dataTable->setItem(row, YEAR - 1, new QTableWidgetItem(QString::number(data->year)));
            ui->dataTable->setItem(row, REPUBLIC - 1, new QTableWidgetItem(data->republic));
            ui->dataTable->setItem(row, NPG - 1, new QTableWidgetItem(QString::number(data->npg)));
            ui->dataTable->setItem(row, BIRTH_RATE - 1, new QTableWidgetItem(QString::number(data->birthRate)));
            ui->dataTable->setItem(row, DEATH_RATE - 1, new QTableWidgetItem(QString::number(data->deathRate)));
            ui->dataTable->setItem(row, GDW - 1, new QTableWidgetItem(QString::number(data->gdw)));
            ui->dataTable->setItem(row, URBANIZATION - 1, new QTableWidgetItem(QString::number(data->urbanization)));

            row++;
        }
    }
}

void MainWindow::on_calculatePushButton_clicked() {
    if (context.list == NULL)
        context.flagErrorCode = EMPTY_LIST;

    if (context.flagErrorCode == SUCCESSFULLY) {
        QString regionFilter = ui->RepublicLineEdit->text();
        QString columnFilter = ui->columnLineEdit->text();

        ParamsUser params;
        params.republic = allocForString(SIZE_BUFFER);
        params.column = columnFilter.toInt();
        strncpy(params.republic, regionFilter.toUtf8().constData(), SIZE_BUFFER - 1);

        doOperation(CALCULATE_METRIC, &context, &params);
        freeString(params.republic);
    }

    if (context.flagErrorCode == SUCCESSFULLY) {
        ui->maximumEdit->setText(QString::number(context.metrics.max));
        ui->minimunEdit->setText(QString::number(context.metrics.min));
        ui->medianEdit->setText(QString::number(context.metrics.median));
    } else
        resetApp();
}

void MainWindow::errorsHandle(StatusCode status) {
    switch(status) {
    case OFFSET_UNDEFINED:
        QMessageBox::warning(this, "Error", "Field offset could not be determined");
        break;
    case ERROR_READ_FILE:
        QMessageBox::warning(this, "Error", "Сould not read the file");
        break;
    case EMPTY_LIST:
        QMessageBox::warning(this, "Error", "The transmitted list turned out to be empty");
        break;
    case ARRAY_NOT_CREATE:
        QMessageBox::warning(this, "Error", "Failed to create an array of metric counts");
        break;
    case EMPTY_ARRAY:
        QMessageBox::warning(this, "Error", "Failed to find data in the metric count array");
        break;
    case FILE_NOT_SELECT:
        QMessageBox::warning(this, "Error", "The file was not selected or could not be opened");
        break;
    case SUCCESSFULLY:
        break;
    }
}

void MainWindow::resetApp() {
    errorsHandle(context.flagErrorCode);
    freeContext(&context);
    resetWindow();
    doOperation(INITIALIZATION, &context, NULL);
}

void MainWindow::resetWindow() {
    ui->dataTable->setRowCount(0);
    ui->minimunEdit->setText("");
    ui->maximumEdit->setText("");
    ui->medianEdit->setText("");
    ui->RepublicLineEdit->setText("");
    ui->columnLineEdit->setText("");
    ui->FileEdit->setText("");
}

void MainWindow::freeContext(AppContext* context) {
    if (context->list != NULL)
        freeList(context->list);
    freeString(context->filename);
    freeString(context->printErrorCode);
}

MainWindow::~MainWindow() {
    freeContext(&context);
    delete ui;
}







