#include <QApplication>

#include "mainwindow.h"
int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale(QLocale::C));
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  s21::ViewerCore* viewerCore = s21::ViewerCore::GetInstance();
  s21::Controller controller(viewerCore);
  s21::MainWindow w(&controller);
  w.show();
  return a.exec();
}
