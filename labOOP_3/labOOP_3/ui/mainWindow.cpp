#include <QMessageBox>

#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectButtons();
    updateDisplay();
}

void MainWindow::run(std::function<void()> action) {
    try {
        action();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
        facade.clear();
    }
    updateDisplay();
}

void MainWindow::updateDisplay() {
    const auto& text = facade.getDisplay();
    ui->userPanel->setText(QString::fromStdString(text.empty() ? "0" : text));
}

void MainWindow::connectButtons() {
    for (auto* button : {
             ui->number_0, ui->number_1, ui->number_2, ui->number_3,
             ui->number_4, ui->number_5, ui->number_6, ui->number_7,
             ui->number_8, ui->number_9,
             ui->dot,
             ui->plus, ui->minus, ui->multiplication, ui->division,
             ui->leftBracket, ui->rightBracket
         })
        bind(button, [this, button] { facade.input(button->text().toStdString()); });

    bind(ui->equal, [this] { facade.calculate(); });
    bind(ui->button_Del, [this] { facade.deleteLast(); });
    bind(ui->button_C, [this] { facade.clear(); });
}

void MainWindow::bind(QPushButton* button, std::function<void()> action) {
    connect(button, &QPushButton::clicked, this, [this, action] { run(action); });
}

MainWindow::~MainWindow() {
    delete ui;
}
