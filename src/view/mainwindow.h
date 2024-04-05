#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credit_calc.h"
#include "smartcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc21;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void on_pushButton_Graph_clicked_true();
    void on_pushButton_Graph_clicked_false();
    void on_toolButton_toSmartCalc_clicked_go();
    void on_pushButton_calcCred_clicked_go();
    void on_checkBox_clicked_true();
    void on_checkBox_clicked_false();
private slots:
    void changeSizeWindow_true();
    void changeSizeWindow_creditCalc();
    void changeSizeWindow_false();
    void changeSize_creditCalcWindowMax();
    void changeSize_creditCalcWindowMin();

private:
    Ui::SmartCalc21 *ui;
    SmartCalc SmartCalc21;
    CreditCalc CreditCalc21;
};
#endif // MAINWINDOW_H
