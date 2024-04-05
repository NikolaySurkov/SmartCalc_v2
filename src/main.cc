#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");
  QCoreApplication::setOrganizationName("*");
  QCoreApplication::setOrganizationDomain("*");
  QCoreApplication::setApplicationName("*");

  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("SmartCalc21");
  w.show();
  return a.exec();
}
