#include "mainwindow.h"

#include <QObject>
#include <QPushButton>
#include <QSizePolicy>

#include "./ui_mainwindow.h"
#include "smartcalc.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartCalc21)
{
    ui->setupUi(this);
    this->setObjectName("SmartCalc21");
    ui->stackedWidgetPages->insertWidget(0, &SmartCalc21);
    ui->stackedWidgetPages->setCurrentIndex(0);
    ui->stackedWidgetPages->insertWidget(1, &CreditCalc21);

    this->setFixedSize(328, 586);
    // this->setFixedSize(601,421); // CreditCalc21
    ui->StackCalc->setStyleSheet("border-radius:0px;");
    connect(&CreditCalc21,
            SIGNAL(on_toolButton_toSmartCalc_clicked_go()),
            this,
            SLOT(changeSizeWindow_false()));
    connect(&CreditCalc21,
            SIGNAL(on_checkBox_clicked_true()),
            this,
            SLOT(changeSize_creditCalcWindowMax()));
    connect(&CreditCalc21,
            SIGNAL(on_checkBox_clicked_false()),
            this,
            SLOT(changeSize_creditCalcWindowMin()));

    connect(&SmartCalc21,
            SIGNAL(on_pushButton_Graph_clicked_true()),
            this,
            SLOT(changeSizeWindow_true())); // получаются данные из формы
    connect(&SmartCalc21,
            SIGNAL(on_pushButton_Graph_clicked_false()),
            this,
            SLOT(changeSizeWindow_false()));
    connect(&SmartCalc21,
            SIGNAL(on_pushButton_calcCred_clicked_go()),
            this,
            SLOT(changeSizeWindow_creditCalc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSizeWindow_false()
{
    this->setFixedSize(328, 586);
    ui->stackedWidgetPages->setCurrentIndex(0);
}

void MainWindow::changeSizeWindow_true()
{
    this->setFixedSize(971, 586);
}

void MainWindow::changeSizeWindow_creditCalc()
{
    this->setFixedSize(550, 420);
    ui->stackedWidgetPages->setCurrentIndex(1);
    on_pushButton_Graph_clicked_false();
}

void MainWindow::changeSize_creditCalcWindowMax()
{
    this->setFixedSize(971, 420);
}

void MainWindow::changeSize_creditCalcWindowMin()
{
    this->setFixedSize(550, 420);
}
