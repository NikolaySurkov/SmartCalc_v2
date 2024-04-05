#include "credit_calc.h"

#include <QDate>
#include <QString>

#include "ui_credit_calc.h"

/// @brief Конструктор
/// @param parent
CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreditCalc)
{
    ui->setupUi(this);
    ui->doubleSpinBox_creditSum->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_creditPeriod->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->doubleSpinBox_creditRate->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->doubleSpinBox_creditSum->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->doubleSpinBox_creditRate->setRange(0.01, 999);
    ui->doubleSpinBox_creditRate->setValue(13.6);
    ui->radiobatton_creditAnnuityPayment->setChecked(true);
    ui->textEdit_1->moveCursor(QTextCursor::Up);
    ui->textEdit_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit_1->setReadOnly(true);
    ui->textEdit_1->setMaximumBlockCount(605);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_2->setMaximumBlockCount(605);
    ui->textEdit_3->setReadOnly(true);
    ui->textEdit_3->setMaximumBlockCount(605);
    ui->textEdit_4->setReadOnly(true);
    ui->textEdit_4->setMaximumBlockCount(605);
    ui->textEdit_5->setReadOnly(true);
    ui->textEdit_5->setMaximumBlockCount(605);
    this->setStyleSheet(QString::fromUtf8("QPushButton:pressed{\n"
                                          " border:2px solid #FFF;\n"
                                          " background-image: none;\n"
                                          " background-color: #000; \n"
                                          " font: 500 10pt ;\n"
                                          " color: #FFF;\n"
                                          " }\n"
                                          " \n"
                                          "QDoubleSpinBox, QSpinBox{\n"
                                          " background-color: rgb(41, 41, 41);\n"
                                          " border:2px solid rgb(186, 185, 183);\n"
                                          " border-radius:5px;\n"
                                          " color:#fff;\n"
                                          " }\n"
                                          " \n"
                                          "QPushButton{\n"
                                          " border:3px solid #000;\n"
                                          " margin:0px;\n"
                                          " border-radius:10px;\n"
                                          " background-color: rgb(186, 185, 183);\n"
                                          " background-image: none;\n"
                                          " font: 500 10pt \"Pet Me\";\n"
                                          " color: #000;\n"
                                          " }\n"
                                          " \n"
                                          "QPushButton::hover{"
                                          "   background-color:rgb(85, 169, 221);"
                                          "   font-size: 10px;"
                                          "   }\n"
                                          "QPlainTextEdit, QLineEdit{\n"
                                          "  background-color: rgb(218, 242, 220);"
                                          "   font-size: 14px;"
                                          "  color:  #000;\n}"
                                          "\n"
                                          "QLineEdit::focus{\n"
                                          "  border: 2px solid #006080;\n"
                                          "\n"
                                          "  color:  #000;\n}"
                                          "\n"
                                          "QFrame{\n"
                                          "    margin:1px;\n"
                                          "    background-color: rgb(41, 41, 41);\n"
                                          "    background-image: none;\n"
                                          "    font: 500 10pt \"Pet Me\";\n"
                                          "    color: #000;\n"
                                          "}\n"
                                          "\n"));
    ui->textEdit_1->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                  "font-size: 10px;\n");
    ui->textEdit_2->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                  "font-size: 10px;\n");
    ui->textEdit_3->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                  "font-size: 10px;\n");
    ui->textEdit_4->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                  "font-size: 10px;\n");
    ui->textEdit_5->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                  "font-size: 10px;\n");
}

/// @brief Деструктор
CreditCalc::~CreditCalc()
{
    delete ui;
}

void CreditCalc::on_toolButton_toSmartCalc_clicked()
{
    this->setFixedSize(550, 421);
    CreditCalc::on_toolButton_toSmartCalc_clicked_go();
    ui->checkBox->stateChanged(0);
    ui->checkBox->setChecked(false);
}

void CreditCalc::on_spinBox_creditPeriod_textChanged(const QString &arg1)
{
    if (ui->comboBox_creditPeriodType->currentIndex() == MONTH) {
        if (arg1.toInt() > 600) {
            ui->label_creditPeriodError->setText(
                "Значение должно быть больше 0 и меньше или равно 600");
            ui->spinBox_creditPeriod->setStyleSheet(" border:3px solid #B00;\n");
            status_eq = false;
        } else {
            ui->label_creditPeriodError->setText("");
            ui->spinBox_creditPeriod->setStyleSheet(" border:0px solid #000;\n");
            status_eq = true;
        }
    } else if (ui->comboBox_creditPeriodType->currentIndex() == YEAR) {
        if (arg1.toInt() > 50) {
            ui->label_creditPeriodError->setText("Значение должно быть меньше или равно 50");
            ui->spinBox_creditPeriod->setStyleSheet(" border:3px solid #B00;\n");
            status_eq = false;
        } else {
            ui->label_creditPeriodError->setText("");
            ui->spinBox_creditPeriod->setStyleSheet(" border:0px solid #000;\n");
            status_eq = true;
        }
    }
}

void CreditCalc::on_comboBox_creditPeriodType_activated(int index)
{
    on_spinBox_creditPeriod_textChanged(ui->spinBox_creditPeriod->text());
}

void CreditCalc::on_pushbutton_creditResultGo_clicked()
{
    if (status_eq == true) {
        CreditCalculculate.CreditCalculate(getSumAmount(),
                                           getPeriod(),
                                           getRate(),
                                           getTypePeriod(),
                                           getTypePay());
        if (getTypePay() == ANNUITIES) {
            ui->lineEdit_creditResultMonthPay->setText(
                QString::number(CreditCalculculate.getMonthlyPayment(), 'f', 2));
            ui->lineEdit_creditResultOverpay->setText(
                QString::number(CreditCalculculate.getOverpayment(), 'f', 2));
            ui->lineEdit_creditResultTotalPay->setText(
                QString::number(CreditCalculculate.getFullAmountPayments(), 'f', 2));
        } else {
            QString result = QString::number(CreditCalculculate.getVectorMonthyPayments().front(),
                                             'f',
                                             2)
                             + "...";
            result += QString::number(CreditCalculculate.getVectorMonthyPayments().back(), 'f', 2);
            ui->lineEdit_creditResultMonthPay->setText(result);
            ui->lineEdit_creditResultOverpay->setText(
                QString::number(CreditCalculculate.getOverpayment(), 'f', 2));
            ui->lineEdit_creditResultTotalPay->setText(
                QString::number(CreditCalculculate.getFullAmountPayments(), 'f', 2));
            std::vector<double> res = CreditCalculculate.getVectorMonthyPayments();
            int count = 1;
            double main_pay = CreditCalculculate.getMainArrearsDiffCalc();
            ui->textEdit_1->clear();
            ui->textEdit_2->clear();
            ui->textEdit_3->clear();
            ui->textEdit_4->clear();
            ui->textEdit_5->clear();
            ui->textEdit_1->insertPlainText(" ID \n");
            ui->textEdit_2->insertPlainText(" Платеж \n");
            ui->textEdit_3->insertPlainText("Основной\n");
            ui->textEdit_4->insertPlainText("Проценты\n");
            ui->textEdit_5->insertPlainText("Остаток\n");
            double total_sum = roundl(getSumAmount());
            for (auto x : res) {
                total_sum -= main_pay;
                ui->textEdit_1->insertPlainText(QString::number(count, 'g', 4) + "\n");
                ui->textEdit_2->insertPlainText(QString::number(x, 'f', 2) + "\n");
                ui->textEdit_3->insertPlainText(QString::number(main_pay, 'f', 2) + "\n");
                ui->textEdit_4->insertPlainText(QString::number(x - main_pay, 'f', 2) + "\n");
                ui->textEdit_5->insertPlainText(
                    QString::number(roundNumberTwoDigits(total_sum), 'f', 2) + "\n");
                ++count;
            }
        }
    }
}

void CreditCalc::on_radiobatton_creditAnnuityPayment_clicked()
{
    type_of_payment = ANNUITIES;
}

void CreditCalc::on_radiobutton_creditDifferentPayment_clicked()
{
    type_of_payment = DIFFERENTIATED;
}

bool CreditCalc::getTypePay()
{
    if (type_of_payment == ANNUITIES)
        return ANNUITIES;
    return DIFFERENTIATED;
}

bool CreditCalc::getTypePeriod()
{
    if (ui->comboBox_creditPeriodType->currentIndex() == MONTH)
        return MONTH;
    return YEAR;
}

double CreditCalc::getSumAmount()
{
    return ui->doubleSpinBox_creditSum->value();
}

int CreditCalc::getPeriod()
{
    return ui->spinBox_creditPeriod->value();
}

double CreditCalc::getRate()
{
    return ui->doubleSpinBox_creditRate->value();
}

void CreditCalc::sizeWindowMax()
{
    this->setFixedSize(971, 422);
}

void CreditCalc::sizeWindowMin()
{
    this->setFixedSize(550, 422);
}

void CreditCalc::on_checkBox_clicked(bool checked)
{
    if (checked) {
        on_checkBox_clicked_true();
        sizeWindowMax();
    } else {
        on_checkBox_clicked_false();
        sizeWindowMin();
    }
}

double CreditCalc::roundNumberTwoDigits(double a)
{
    double res = a;
    res = a * 100.0;
    res = roundl(res);
    res = res / 100.0;
    return res;
}
