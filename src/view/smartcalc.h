#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QWidget>

#include "../controller/controller_smart_calc.h"
#include "view/QCustomPlot/qcustomplot.h"

namespace Ui {
class SmartCalc;
}
/// @brief класс графического представления SmartCalc
class SmartCalc : public QWidget
{
    Q_OBJECT

public:
    /// @brief Конструктор с одним параметром
    /// @param parent QWidget *
    explicit SmartCalc(QWidget *parent = nullptr);

    /// @brief деструктор класса SmartCalc
    ~SmartCalc();

signals:
    void on_pushButton_Graph_clicked_true();
    void on_pushButton_Graph_clicked_false();
    void on_pushButton_calcCred_clicked_go();

private slots:
    void on_pushButton_Graph_toggled(bool checked);
    void increaseValueXGraph();
    void increaseValueYGraph();
    void decreaseValueXGraph();
    void decreaseValueYGraph();
    void clearGraph();
    void makeGraph();
    void on_spinBox_Yend_textChanged(const QString &arg1);

    void on_spinBox_Ybegin_textChanged(const QString &arg1);

    void on_spinBox_Xbegin_textChanged(const QString &arg1);

    void on_spinBox_Xend_textChanged(const QString &arg1);
    void buttonInput_clicked();
    void on_lineEdit_xValue_textChanged(const QString &arg1);
    void keyPressEvent(QKeyEvent *event);
    //    void on_plainTextEdit_OUTPUT_cursorPositionChanged();
    void showPointToolTip(QMouseEvent *event);
    void on_toolButton_OK_clicked();

    void on_pushButton_calcCred_clicked();

private:
    void smartCalcStyleBegin();
    void clickPushButtonResult();
    void clickPushButtonClear();
    void sizeWindowMin();
    void sizeWindowMax();
    void changingScopeOfTheGraph();
    void graphDefault();
    void validationQlineEdit();
    bool eventFilter(QObject *watched, QEvent *event);

    Ui::SmartCalc *ui;
    QCustomPlot *Graph;
    calc::Controller controller;
    QObject *m_focused = nullptr;
    double x_begin_ = -9;
    double x_end_ = 9;
    double y_begin_ = -6;
    double y_end_ = 12;
    QRegularExpressionValidator *validator = nullptr;
};

#endif // SMARTCALC_H
