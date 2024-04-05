#include "smartcalc.h"

#include <QButtonGroup>
#include <QComboBox>
#include <QFontDatabase>
#include <QGraphicsEffect>
#include <QGraphicsScene>
#include <QList>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QStyleOption>
#include <QTabBar>
#include <QTextStream>
#include <QWidget>
#include <iostream>

#include "ui_smartcalc.h"
SmartCalc::SmartCalc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartCalc)
{
    setlocale(LC_NUMERIC, "C");
    ui->setupUi(this);
    Graph = new QCustomPlot();
    ui->GraphWidget->insertWidget(0, Graph);
    ui->GraphWidget->setCurrentIndex(0);
    this->smartCalcStyleBegin();
    this->sizeWindowMin();
    this->graphDefault();
    this->validationQlineEdit();

    ui->lineEdit_MAIN_STR->installEventFilter(this);
    ui->lineEdit_xValue->installEventFilter(this);
    connect(this->Graph,
            SIGNAL(mouseMove(QMouseEvent *)),
            this,
            SLOT(showPointToolTip(QMouseEvent *)));
    connect(ui->toolButton_Up, SIGNAL(clicked()), this, SLOT(increaseValueYGraph()));
    connect(ui->toolButton_Down, SIGNAL(clicked()), this, SLOT(decreaseValueYGraph()));
    connect(ui->toolButton_Right, SIGNAL(clicked()), this, SLOT(increaseValueXGraph()));
    connect(ui->toolButton_Left, SIGNAL(clicked()), this, SLOT(decreaseValueXGraph()));
    connect(ui->toolButton_ClearGraph, SIGNAL(clicked()), this, SLOT(clearGraph()));
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_PLUS, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_MINUS, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_MULT, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_POW, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_DEV, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_OpenBracket, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_CloseBracket, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_Point, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_PI, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_cleanStr, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->pushButton_calcCred, SIGNAL(clicked()), this, SLOT(clearGraph()));
    connect(ui->pushButton_calcDep, SIGNAL(clicked()), this, SLOT(clearGraph()));
    connect(ui->pushButton_EQ, SIGNAL(clicked()), this, SLOT(buttonInput_clicked()));
    connect(ui->toolButton_OK, SIGNAL(clicked()), this, SLOT(on_toolButton_OK_clicked()));

    SmartCalc::makeGraph();
}

SmartCalc::~SmartCalc()
{
    delete validator;
    delete Graph;
    delete ui;
}

// CLICK " = "
void SmartCalc::buttonInput_clicked()
{
    QPushButton *button = (QPushButton *) sender();
    QString className = button->property("type").toString();
    QLineEdit *line_input = nullptr;
    if (m_focused != nullptr) {
        line_input = static_cast<QLineEdit *>(m_focused);
        line_input->setFocus();

    } else {
        ui->lineEdit_MAIN_STR->setFocusPolicy(Qt::StrongFocus);
        ui->lineEdit_MAIN_STR->setFocus();
        line_input = static_cast<QLineEdit *>(m_focused);
    }

    if (className == "=") {
        this->clickPushButtonResult();
    } else if (className == "clear") {
        if (ui->lineEdit_MAIN_STR->text() == "") {
            ui->plainTextEdit_OUTPUT->clear();
            ui->lineEdit_xValue->clear();
            ui->lineEdit_MAIN_STR->setFocusPolicy(Qt::StrongFocus);
            ui->lineEdit_MAIN_STR->setFocus();
        } else {
            ui->lineEdit_MAIN_STR->clear();
        }
    } else if (className == "del") {
        QString strImputText = line_input->text();
        strImputText.chop(1);
        line_input->setText(strImputText);
    } else {
        line_input->insert(className);
    }
}

void SmartCalc::makeGraph()
{
    QVector<double> x, y;

    x.push_back(-8);
    x.push_back(-6);
    x.push_back(-2);
    x.push_back(1);
    x.push_back(5);
    x.push_back(7);
    x.push_back(9);
    y.push_back(1);
    y.push_back(2);
    y.push_back(0);
    y.push_back(2);
    y.push_back(1);
    y.push_back(-4);
    y.push_back(-3);
    Graph->addGraph();

    Graph->graph(0)->setData(x, y);
    x.clear();
    y.clear();

    x.push_back(-3);
    x.push_back(0);
    x.push_back(3);
    x.push_back(5);
    x.push_back(9);
    y.push_back(6);
    y.push_back(8);
    y.push_back(7);
    y.push_back(5);
    y.push_back(7);
    Graph->addGraph();
    Graph->graph(1)->setData(x, y);
    x.clear();
    y.clear();
    x.push_back(1);
    x.push_back(3);
    x.push_back(3);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(6);
    x.push_back(6);

    y.push_back(2);
    y.push_back(7);
    y.push_back(9);
    y.push_back(10);
    y.push_back(11);
    y.push_back(11);
    y.push_back(10);
    y.push_back(9);

    Graph->addGraph();
    Graph->graph(2)->setData(x, y);
    x.clear();
    y.clear();
    x.push_back(6);
    x.push_back(5);
    x.push_back(4);
    x.push_back(3);
    y.push_back(9);
    y.push_back(8);
    y.push_back(8);
    y.push_back(9);
    Graph->addGraph();
    Graph->graph(3)->setData(x, y);
    x.clear();
    y.clear();
    QVector<double> xx = {4, 4.2, 4.3, 4.50, 4.7, 4.8, 5};
    QVector<double> yy = {9, 8.8, 8.7, 8.65, 8.7, 8.8, 9};
    x = xx;
    y = yy;
    Graph->addGraph();
    Graph->graph(4)->setData(x, y);
    x.clear();
    y.clear();
    x = {3.5, 3.7, 4, 4.3, 4.4};
    y = {10, 10.2, 10.3, 10.2, 10};
    Graph->addGraph();
    Graph->graph(5)->setData(x, y);
    x.clear();
    y.clear();
    x = {4.6, 4.7, 5, 5.3, 5.5};
    y = {10, 10.2, 10.3, 10.2, 10};
    Graph->addGraph();
    Graph->graph(6)->setData(x, y);
    x.clear();
    y.clear();
    Graph->xAxis->setLabel("X - MAN");
    Graph->yAxis->setLabel("y");
    Graph->setInteraction(QCP::iRangeZoom,
                          true); // увеличение - уменьшение Графикa
    Graph->setInteraction(QCP::iRangeDrag, true); // передвинуть

    Graph->replot();
}

void SmartCalc::smartCalcStyleBegin()
{
    this->setStyleSheet("color: #000;\n");
    this->setStyleSheet(QString::fromUtf8("QPushButton:pressed{\n"
                                          " border:2px solid #FFF;\n"
                                          " background-image: none;\n"
                                          " background-color: #000; \n"
                                          " font: 500 10pt ;\n"
                                          " color: #FFF;\n"
                                          " }\n"
                                          " \n"
                                          "QToolButton:pressed{\n"
                                          " border:1px solid #000;\n"
                                          " background-image: none;\n"
                                          " background-color: rgb(218, 242, 220); \n"
                                          " font: 100 10pt ;\n"
                                          " border-radius: 6px;"
                                          " }\n"
                                          " \n"
                                          "QToolButton{\n"
                                          "border: 2px solid #000;\n"
                                          " color: #000;\n"
                                          " background-image: none;\n"
                                          " background-color:rgb(218, 242, 220);\n"
                                          " border-radius: 6px;}\n"
                                          "\n"
                                          "QToolButton:pressed#toolButton_OK{\n"
                                          "border: 1px solid #00BFFF;\n"
                                          " background-image: none;\n"
                                          " background-color:rgb(186, 185, 183);\n"
                                          " border-radius: 10px;}\n"
                                          "\n"
                                          "QToolButton#toolButton_OK{\n"
                                          "border: 1px solid #000, 20, 60;\n"
                                          " background-image: none;\n"
                                          " background-color:rgb(186, 185, 183);\n"
                                          " margin: 5px;\n"
                                          " border-radius: 10px;}\n"
                                          "\n"
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
                                          " color: #000;\n"
                                          " }\n"
                                          " \n"
                                          "QPushButton::hover{"
                                          "   background-color:rgb(85, 169, 221);"
                                          "   font-size: 10px;"
                                          "   }\n"
                                          "QPlainTextEdit, QLineEdit{\n"
                                          "  background-color: rgb(218, 242, 220);"
                                          "   font-size: 18px;"
                                          "  color:  #000;\n}"
                                          "\n"
                                          "QLineEdit::focus{\n"
                                          "  border: 2px solid #006080;\n"
                                          "\n"
                                          "  color:  #000;\n}"
                                          "\n"
                                          "QFrame{\n"
                                          "    margin:0px;\n"
                                          "    background-color: rgb(41, 41, 41);\n"
                                          "    background-image: none;\n"
                                          "    color: #000;\n"
                                          "}\n"
                                          "\n"));

    ui->lineEdit_MAIN_STR->setStyleSheet("color:  #000;\n\n");
    ui->plainTextEdit_OUTPUT->setStyleSheet("background-color: rgb(218, 242, 220); \n"
                                            "font-size: 21px;\n");
    ui->lineEdit_MAIN_STR->setStyleSheet("QLineEdit::focus{\n"
                                         "border: 2px solid #006080;\n"
                                         "color:  #000;\n}\n");
    ui->spinBox_Xbegin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_Xend->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_Ybegin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_Yend->setButtonSymbols(QAbstractSpinBox::NoButtons);
    this->Graph->setBackground(QBrush("#DCDCDC"));
    ui->plainTextEdit_OUTPUT->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit_OUTPUT->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit_OUTPUT->setReadOnly(true);
    ui->plainTextEdit_OUTPUT->setMaximumBlockCount(300);
}

void SmartCalc::clickPushButtonResult()
{
    if (ui->lineEdit_MAIN_STR->text().contains('x') && ui->lineEdit_xValue->text() == "") {
        ui->lineEdit_xValue->setFocusPolicy(Qt::StrongFocus);
        ui->lineEdit_xValue->setFocus();
    } else if (ui->lineEdit_MAIN_STR->text() != "") {
        ui->lineEdit_MAIN_STR->setFocusPolicy(Qt::StrongFocus);
        ui->lineEdit_MAIN_STR->setFocus();
        ui->plainTextEdit_OUTPUT->verticalScrollBar()->setSliderPosition(
            ui->plainTextEdit_OUTPUT->verticalScrollBar()->maximum());
        QTextCursor cursor = ui->plainTextEdit_OUTPUT->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->plainTextEdit_OUTPUT->setTextCursor(cursor);

        try {
            controller.CalcMath(ui->lineEdit_MAIN_STR->text().toStdString(),
                                ui->lineEdit_xValue->text().toDouble());
            ui->plainTextEdit_OUTPUT->insertPlainText("\n" + ui->lineEdit_MAIN_STR->text() + "\n");
            ui->plainTextEdit_OUTPUT->verticalScrollBar()->setValue(
                ui->plainTextEdit_OUTPUT->verticalScrollBar()->maximumHeight());
            ui->plainTextEdit_OUTPUT->insertPlainText(
                "=" + QString::number(controller.getAnswer(), 'g', 16));
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Warning", e.what());
        }
    }
}

void SmartCalc::sizeWindowMin()
{
    this->setFixedSize(330, 586);
    ui->plainTextEdit_OUTPUT->setFixedWidth(311);
    ui->lineEdit_xValue->setFixedWidth(311);
    ui->lineEdit_MAIN_STR->setFixedWidth(311);
    ui->frame_Strings->setFixedWidth(311);
}

void SmartCalc::sizeWindowMax()
{
    this->setFixedSize(971, 588);
    ui->plainTextEdit_OUTPUT->setFixedWidth(412);
    ui->lineEdit_xValue->setFixedWidth(412);
    ui->lineEdit_MAIN_STR->setFixedWidth(412);
    ui->frame_Strings->setFixedWidth(412);
}

void SmartCalc::changingScopeOfTheGraph()
{
    Graph->xAxis->setRange(ui->spinBox_Xbegin->value(), ui->spinBox_Xend->value());
    Graph->yAxis->setRange(ui->spinBox_Ybegin->value(), ui->spinBox_Yend->value());
    Graph->replot();
}

void SmartCalc::graphDefault()
{
    ui->spinBox_Ybegin->setValue(-6);
    ui->spinBox_Yend->setValue(12);
    ui->spinBox_Xbegin->setValue(-9);
    ui->spinBox_Xend->setValue(9);
    Graph->xAxis->setRange(ui->spinBox_Xbegin->value(), ui->spinBox_Xend->value());
    Graph->yAxis->setRange(ui->spinBox_Ybegin->value(), ui->spinBox_Yend->value());
    Graph->xAxis->setLabel("X");
    Graph->yAxis->setLabel("Y");
    Graph->replot();
}

void SmartCalc::validationQlineEdit()
{
    QRegularExpression re("[^~#$&@!`\"\':;<>,]+\\]\\[{}\\?/>№]");
    validator = new QRegularExpressionValidator(re, NULL);
    ui->lineEdit_MAIN_STR->setValidator(validator);
}

bool SmartCalc::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        m_focused = watched;
    }
    return false;
}

void SmartCalc::on_pushButton_Graph_toggled(bool checked)
{
    if (checked) {
        SmartCalc::on_pushButton_Graph_clicked_true();
        SmartCalc::sizeWindowMax();
    } else {
        SmartCalc::on_pushButton_Graph_clicked_false();
        SmartCalc::sizeWindowMin();
    }
}

void SmartCalc::increaseValueXGraph()
{
    ui->spinBox_Xbegin->setValue(ui->spinBox_Xbegin->value() + 1);
    ui->spinBox_Xend->setValue(ui->spinBox_Xend->value() + 1);
    changingScopeOfTheGraph();
}

void SmartCalc::increaseValueYGraph()
{
    ui->spinBox_Ybegin->setValue(ui->spinBox_Ybegin->value() + 1);
    ui->spinBox_Yend->setValue(ui->spinBox_Yend->value() + 1);
    changingScopeOfTheGraph();
}

void SmartCalc::decreaseValueXGraph()
{
    ui->spinBox_Xbegin->setValue(ui->spinBox_Xbegin->value() - 1);
    ui->spinBox_Xend->setValue(ui->spinBox_Xend->value() - 1);
    changingScopeOfTheGraph();
}

void SmartCalc::decreaseValueYGraph()
{
    ui->spinBox_Ybegin->setValue(ui->spinBox_Ybegin->value() - 1);
    ui->spinBox_Yend->setValue(ui->spinBox_Yend->value() - 1);
    changingScopeOfTheGraph();
}

void SmartCalc::clearGraph()
{
    if (!Graph->graphCount()) {
        makeGraph();
    } else {
        Graph->clearGraphs();
        SmartCalc::graphDefault();
    }
}

void SmartCalc::on_spinBox_Yend_textChanged(const QString &arg1)
{
    if (arg1.size()) {
        bool ok = false;
        ui->spinBox_Yend->setValue(arg1.toInt(&ok, 10));
        Graph->yAxis->setRange(ui->spinBox_Ybegin->value(), ui->spinBox_Yend->value());
        y_end_ = ui->spinBox_Yend->value();
        Graph->replot();
    }
}

void SmartCalc::on_spinBox_Ybegin_textChanged(const QString &arg1)
{
    if (arg1.size()) {
        bool ok = false;
        ui->spinBox_Ybegin->setValue(arg1.toInt(&ok, 10));
        Graph->yAxis->setRange(ui->spinBox_Ybegin->value(), ui->spinBox_Yend->value());
        y_begin_ = ui->spinBox_Ybegin->value();
        Graph->replot();
    }
}

void SmartCalc::on_spinBox_Xbegin_textChanged(const QString &arg1)
{
    if (arg1.size()) {
        bool ok = false;
        ui->spinBox_Xbegin->setValue(arg1.toInt(&ok, 10));
        Graph->xAxis->setRange(ui->spinBox_Xbegin->value(), ui->spinBox_Xend->value());
        x_begin_ = ui->spinBox_Xbegin->value();
        Graph->replot();
    }
}

void SmartCalc::on_spinBox_Xend_textChanged(const QString &arg1)
{
    if (arg1.size()) {
        bool ok = false;
        ui->spinBox_Xend->setValue(arg1.toInt(&ok, 10));
        Graph->xAxis->setRange(ui->spinBox_Xbegin->value(), ui->spinBox_Xend->value());
        x_end_ = ui->spinBox_Xend->value();
        Graph->replot();
    }
}

void SmartCalc::on_lineEdit_xValue_textChanged(const QString &arg1)
{
    QString arg = arg1;
    if (*arg.begin() == '.') {
        arg = ("0" + arg);
    }
    QDoubleValidator *validator = new QDoubleValidator(-111111111111111111,
                                                       111111111111111111,
                                                       7,
                                                       this);
    validator->setLocale(QLocale::Latin);
    ui->lineEdit_xValue->setValidator(validator);
    ui->lineEdit_xValue->setText(arg);
}

void SmartCalc::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return && !event->isAutoRepeat()) {
        ui->pushButton_EQ->click();
    } else if (event->key() == Qt::Key_Backspace && !event->isAutoRepeat()) {
        ui->pushButton_del->click();
    }
}

void SmartCalc::on_toolButton_OK_clicked()
{
    Graph->clearGraphs();

    Graph->setInteraction(QCP::iRangeZoom,
                          true); // увеличение - уменьшение Графикa
    Graph->setInteraction(QCP::iRangeDrag, true); // передвинуть

    Graph->xAxis->setRange(ui->spinBox_Xbegin->value(), ui->spinBox_Xend->value());
    Graph->yAxis->setRange(ui->spinBox_Ybegin->value(), ui->spinBox_Yend->value());

    try {
        controller.GraphCreate(ui->lineEdit_MAIN_STR->text().toStdString(),
                               x_begin_,
                               x_end_,
                               y_begin_,
                               y_end_);
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Warning", e.what());
    }

    std::vector<double> a, b;
    a = controller.getVectorX();
    b = controller.getVectorY();
    QVector<double> x(a.begin(), a.end());
    QVector<double> y(b.begin(), b.end());
    Graph->addGraph();
    Graph->graph()->setLineStyle(QCPGraph::lsLine);
    Graph->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    Graph->graph()->setPen(QPen(QColor::fromRgb(0, 102, 102)));
    Graph->graph()->addData(x, y);
    Graph->xAxis->setLabel("X \"" + ui->lineEdit_MAIN_STR->text() + "\"");
    Graph->replot();
}

void SmartCalc::showPointToolTip(QMouseEvent *event)
{
    double x = Graph->xAxis->pixelToCoord(event->pos().x());
    double y = Graph->yAxis->pixelToCoord(event->pos().y());

    Graph->setToolTip(QString("%1 , %2").arg(x).arg(y));
}

void SmartCalc::on_pushButton_calcCred_clicked()
{
    sizeWindowMin();
    ui->pushButton_Graph->setChecked(false);
    SmartCalc::on_pushButton_calcCred_clicked_go();
}
