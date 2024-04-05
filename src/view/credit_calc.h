#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QWidget>

#include "../controller/controller_credit_calc.h"
namespace Ui {
class CreditCalc;
}
enum PeriodType : bool {
    MONTH,
    YEAR,
};
enum TypePay : bool {
    ANNUITIES,
    DIFFERENTIATED,
};
class CreditCalc : public QWidget
{
    Q_OBJECT

public:
    explicit CreditCalc(QWidget *parent = nullptr);
    ~CreditCalc();
signals:
    void on_toolButton_toSmartCalc_clicked_go();
    void on_checkBox_clicked_true();
    void on_checkBox_clicked_false();
private slots:
    void on_toolButton_toSmartCalc_clicked();

    void on_spinBox_creditPeriod_textChanged(const QString &arg1);

    void on_comboBox_creditPeriodType_activated(int index);

    void on_pushbutton_creditResultGo_clicked();

    void on_radiobatton_creditAnnuityPayment_clicked();

    void on_radiobutton_creditDifferentPayment_clicked();

    void on_checkBox_clicked(bool checked);

    double roundNumberTwoDigits(double a);

private:
    Ui::CreditCalc *ui;
    calc::ControllerCreditCalc CreditCalculculate;
    bool type_of_payment = ANNUITIES;
    bool getTypePay();
    bool getTypePeriod();
    double getSumAmount();
    int getPeriod();
    double getRate();
    bool status_eq = true;
    void sizeWindowMax();
    void sizeWindowMin();
};

#endif // CREDIT_CALC_H
