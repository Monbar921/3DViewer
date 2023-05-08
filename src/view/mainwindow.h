#ifndef CPP4_3DVIEWER_V2_0_VIEW_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_VIEW_MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "QtGifImage/qgifimage.h"
#include "controller.h"
#include "gemmaglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButtonSelectFile_clicked();

  void on_pushButtonSelectColorLine_clicked();

  void on_pushButtonSelectColorVertex_clicked();

  void on_pushButtonSelectColorBG_clicked();

  void on_pushButtonOpenFile_clicked();

  void on_pushButtonSelectColorFace_clicked();

  void on_mainGLWidget_scaleChanged(float scale);

  void on_mainGLWidget_mainObjShifted();

  void on_mainGLWidget_mainObjResetted();

  void on_mainGLWidget_mainObjRotated();

  void on_scrollBarAngleX_valueChanged(int value);

  void on_scrollBarScale_valueChanged(int value);

  void on_scrollBarShiftX_valueChanged(int value);

  void on_spinBoxShiftX_valueChanged(int arg1);

  void on_scrollBarShiftY_valueChanged(int value);

  void on_spinBoxShiftY_valueChanged(int arg1);

  void on_scrollBarShiftZ_valueChanged(int value);

  void on_spinBoxShiftZ_valueChanged(int arg1);

  void on_spinBoxAngleX_valueChanged(int arg1);

  void on_scrollBarAngleY_valueChanged(int value);

  void on_spinBoxAngleY_valueChanged(int arg1);

  void on_scrollBarAngleZ_valueChanged(int value);

  void on_spinBoxAngleZ_valueChanged(int arg1);

  void on_comboBoxProjectionType_currentIndexChanged(int index);

  void on_comboBoxEdgesType_currentIndexChanged(int index);

  void on_spinBoxEdgesSize_valueChanged(int arg1);

  void on_comboBoxVertexType_currentIndexChanged(int index);

  void on_spinBoxVertexesSize_valueChanged(int arg1);

  void on_comboBoxFacesType_currentIndexChanged(int index);

  void on_pushButtonSaveIMG_clicked();

  void on_pushButtonSaveGIF_clicked();

  void createGIF();

  void on_pushButtonResetObj_clicked();

 private:
  Controller *controller_;

  Ui::MainWindow *ui_;
  QString full_filename_;
  QString short_filename_;
  QColor line_color_;
  QColor vertex_color_;
  QColor face_color_;
  QColor background_color_;
  QSettings *settings_;
  QTimer *gif_time_;
  QGifImage *gif_;

  void ShowScaleValue(float scale);
  void InitializeSettings();
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_VIEW_MAINWINDOW_H
