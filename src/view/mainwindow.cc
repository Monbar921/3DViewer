#include "mainwindow.h"

#include "./ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : controller_(controller),
      QMainWindow(parent),
      ui_(new Ui::MainWindow),
      gif_time_(new QTimer) {
  ui_->setupUi(this);
  ui_->mainGLWidget->controller_ = controller_;
  ui_->mainGLWidget->SetObjPtr(controller_->GetObjPtr());
  settings_ = new QSettings(QSettings::NativeFormat, QSettings::UserScope,
                            "GeamTeam", "3DViewer");
  InitializeSettings();
  connect(gif_time_, SIGNAL(timeout()), this, SLOT(createGIF()));
}

MainWindow::~MainWindow() {
  delete ui_->mainGLWidget->default_state_keeper_;
  delete settings_;
  delete ui_;
  delete gif_time_;
}

void MainWindow::InitializeSettings() {
  // ui_->mainGLWidget->controller_ = controller_;
  unsigned projection_type = settings_->value("Projection/Type", 1).toUInt();
  ui_->mainGLWidget->SetProjectionType((ProjectionType)projection_type);
  ui_->comboBoxProjectionType->setCurrentIndex(projection_type);

  unsigned edges_type = settings_->value("Edges/Type", 0).toUInt();
  ui_->mainGLWidget->SetEdgesType((EdgesType)edges_type);
  ui_->comboBoxEdgesType->setCurrentIndex(edges_type);
  unsigned edges_size = settings_->value("Edges/Size", 1).toUInt();
  ui_->mainGLWidget->SetEdgesSize(edges_size);
  ui_->spinBoxEdgesSize->setValue(edges_size);
  line_color_ =
      QColor(settings_->value("Edges/Color", QString("#FF0000")).toString());
  ui_->mainGLWidget->SetEdgesColor(line_color_);
  ui_->pushButtonSelectColorLine->setStyleSheet(
      "background-color:" + line_color_.name() + ";");

  unsigned vertexes_type = settings_->value("Vertexes/Type", 0).toUInt();
  ui_->mainGLWidget->SetVertexType((VertexType)vertexes_type);
  ui_->comboBoxVertexType->setCurrentIndex(vertexes_type);
  unsigned vertexes_size = settings_->value("Vertexes/Size", 1).toUInt();
  ui_->mainGLWidget->SetVertexesSize(vertexes_size);
  ui_->spinBoxVertexesSize->setValue(vertexes_size);
  vertex_color_ =
      QColor(settings_->value("Vertexes/Color", "#00FF00").toString());
  ui_->mainGLWidget->SetVertexesColor(vertex_color_);
  ui_->pushButtonSelectColorVertex->setStyleSheet(
      "background-color:" + vertex_color_.name() + ";");

  unsigned faces_type = settings_->value("Faces/Type", 0).toUInt();
  ui_->mainGLWidget->SetFacesType((FacesType)faces_type);
  ui_->comboBoxFacesType->setCurrentIndex(faces_type);
  face_color_ = QColor(settings_->value("Faces/Color", "#0000FF").toString());
  ui_->mainGLWidget->SetFacesColor(face_color_);
  ui_->pushButtonSelectColorFace->setStyleSheet(
      "background-color:" + face_color_.name() + ";");

  background_color_ =
      QColor(settings_->value("Background/Color", "#FFFFFF").toString());
  ui_->mainGLWidget->SetBackGroundColor(background_color_);
  ui_->pushButtonSelectColorBG->setStyleSheet(
      "background-color:" + background_color_.name() + ";");
}

void MainWindow::on_pushButtonSelectFile_clicked() {
  full_filename_ = QFileDialog::getOpenFileName(this, "Select OBJ file",
                                                QDir::homePath(), "*.obj");
  ui_->lineEditFullFileName->setText(full_filename_);
  qsizetype tmp = full_filename_.lastIndexOf('/');
  short_filename_ = full_filename_.mid(tmp + 1);
}

void MainWindow::on_pushButtonSelectColorLine_clicked() {
  line_color_ = QColorDialog::getColor();
  ui_->pushButtonSelectColorLine->setStyleSheet(
      "background-color:" + line_color_.name() + ";");
  ui_->mainGLWidget->SetEdgesColor(line_color_);
  settings_->setValue("Edges/Color", line_color_.name());
}

void MainWindow::on_pushButtonSelectColorVertex_clicked() {
  vertex_color_ = QColorDialog::getColor();
  ui_->pushButtonSelectColorVertex->setStyleSheet(
      "background-color:" + vertex_color_.name() + ";");
  ui_->mainGLWidget->SetVertexesColor(vertex_color_);
  settings_->setValue("Vertexes/Color", vertex_color_.name());
}

void MainWindow::on_pushButtonSelectColorFace_clicked() {
  face_color_ = QColorDialog::getColor();
  ui_->pushButtonSelectColorFace->setStyleSheet(
      "background-color:" + face_color_.name() + ";");
  ui_->mainGLWidget->SetFacesColor(face_color_);
  settings_->setValue("Faces/Color", face_color_.name());
}

void MainWindow::on_mainGLWidget_scaleChanged(float scale) {
  ShowScaleValue(scale);
  ui_->scrollBarScale->setValue(ui_->mainGLWidget->main_obj_scale_);
}

void MainWindow::on_mainGLWidget_mainObjShifted() {
  ui_->spinBoxShiftX->setValue(ui_->mainGLWidget->main_obj_x_shift * 10);
  ui_->spinBoxShiftY->setValue(ui_->mainGLWidget->main_obj_y_shift * 10);
}

void MainWindow::on_mainGLWidget_mainObjResetted() {
  ui_->scrollBarScale->setValue(1.0);
  ui_->spinBoxShiftX->setValue(0);
  ui_->spinBoxShiftY->setValue(0);
  ui_->spinBoxShiftZ->setValue(0);
  ui_->spinBoxAngleX->setValue(0);
  ui_->spinBoxAngleY->setValue(0);
  ui_->spinBoxAngleZ->setValue(0);
}

void MainWindow::on_mainGLWidget_mainObjRotated() {
  ui_->spinBoxAngleX->setValue(ui_->mainGLWidget->main_obj_x_angle);
  ui_->spinBoxAngleY->setValue(ui_->mainGLWidget->main_obj_y_angle);
}

void MainWindow::on_pushButtonSelectColorBG_clicked() {
  background_color_ = QColorDialog::getColor();
  ui_->mainGLWidget->SetBackGroundColor(background_color_);
  ui_->pushButtonSelectColorBG->setStyleSheet(
      "background-color:" + background_color_.name() + ";");
  settings_->setValue("background/Color", background_color_.name());
}

void MainWindow::on_pushButtonOpenFile_clicked() {
  ErrorsType status;
  if (full_filename_.isEmpty()) {
    ui_->statusbar->setStyleSheet("background-color:rgb(250, 250, 150);");
    ui_->statusbar->showMessage("Select OBJ file first");
  } else {
    status = controller_->GetObjData(full_filename_.toUtf8().constData());
    ui_->mainGLWidget->main_obj_scale_ = 1;
    ui_->mainGLWidget->update();
    ui_->labelScale->setText("1 : 1");
  }
  if (status == ErrorsType::kSuccess) {
    ui_->mainGLWidget->DefaultStateKeep();
    ui_->labelFileVal->setText(short_filename_);
    ui_->labelVertexesVal->setText(
        QString::number(ui_->mainGLWidget->main_obj_->vertexes_number));
    ui_->labelEdgesVal->setText(QString::number(
        ui_->mainGLWidget->main_obj_->all_faces_vertexes_number));
    ui_->labelFacesVal->setText(
        QString::number(ui_->mainGLWidget->main_obj_->faces_number));
    ui_->statusbar->setStyleSheet("background-color: rgb(143, 240, 164);");
    ui_->statusbar->showMessage("File " + short_filename_ +
                                " opened successfully");
    ui_->mainGLWidget->update();
  } else if (status == ErrorsType::kErrOpen) {
    ui_->statusbar->setStyleSheet("background-color: rgb(255, 150, 150);");
    ui_->statusbar->showMessage("File " + short_filename_ +
                                " does not exist or is not available");
  } else if (status == ErrorsType::kErr3DFormat) {
    ui_->statusbar->setStyleSheet("background-color: rgb(255, 150, 150);");
    ui_->statusbar->showMessage("File " + short_filename_ +
                                " contains wrong OBJ format");
  }
}

void MainWindow::on_scrollBarShiftX_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_x_shift = value / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxShiftX->setValue(value);
}

void MainWindow::on_spinBoxShiftX_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_x_shift = arg1 / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarShiftX->setValue(arg1);
}

void MainWindow::on_scrollBarShiftY_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_y_shift = value / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxShiftY->setValue(value);
}

void MainWindow::on_spinBoxShiftY_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_y_shift = arg1 / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarShiftY->setValue(arg1);
}

void MainWindow::on_scrollBarShiftZ_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_z_shift = value / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxShiftZ->setValue(value);
}

void MainWindow::on_spinBoxShiftZ_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_z_shift = arg1 / 10.0;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarShiftZ->setValue(arg1);
}

void MainWindow::on_scrollBarAngleX_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_x_angle = value;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxAngleX->setValue(value);
}

void MainWindow::on_spinBoxAngleX_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_x_angle = arg1;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarAngleX->setValue(arg1);
}

void MainWindow::on_scrollBarAngleY_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_y_angle = value;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxAngleY->setValue(value);
}

void MainWindow::on_spinBoxAngleY_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_y_angle = arg1;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarAngleY->setValue(arg1);
}

void MainWindow::on_scrollBarAngleZ_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_z_angle = value;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->spinBoxAngleZ->setValue(value);
}

void MainWindow::on_spinBoxAngleZ_valueChanged(int arg1) {
  ui_->mainGLWidget->main_obj_z_angle = arg1;
  ui_->mainGLWidget->ApplyTransformToObj();
  ui_->scrollBarAngleZ->setValue(arg1);
}

void MainWindow::on_scrollBarScale_valueChanged(int value) {
  ui_->mainGLWidget->main_obj_scale_ = value;
  ui_->mainGLWidget->ApplyTransformToObj();
  ShowScaleValue(ui_->mainGLWidget->main_obj_->scaled_with);
}

void MainWindow::ShowScaleValue(float scale) {
  QString scale_mess;
  if (abs(scale - 1) < 0.01) {
    scale_mess = "1 : 1";
  } else if (scale > 10) {
    scale_mess = QString::number(scale, 'f', 0) + " : 1";
  } else if (scale > 1) {
    scale_mess = QString::number(scale, 'f', 1) + " : 1";
  } else if (scale > 0.1) {
    scale_mess = "1 : " + QString::number(1.0 / scale, 'f', 1);
  } else {
    scale_mess = "1 : " + QString::number(1.0 / scale, 'f', 0);
  }
  ui_->labelScale->setText(scale_mess);
}

void MainWindow::on_comboBoxProjectionType_currentIndexChanged(int index) {
  ui_->mainGLWidget->SetProjectionType((ProjectionType)index);
  settings_->setValue("Projection/Type", index);
}

void MainWindow::on_comboBoxEdgesType_currentIndexChanged(int index) {
  ui_->mainGLWidget->SetEdgesType((EdgesType)index);
  settings_->setValue("Edges/Type", index);
}

void MainWindow::on_spinBoxEdgesSize_valueChanged(int arg1) {
  ui_->mainGLWidget->SetEdgesSize(arg1);
  settings_->setValue("Edges/Size", arg1);
}

void MainWindow::on_comboBoxVertexType_currentIndexChanged(int index) {
  ui_->mainGLWidget->SetVertexType((VertexType)index);
  settings_->setValue("Vertexes/Type", index);
}

void MainWindow::on_spinBoxVertexesSize_valueChanged(int arg1) {
  ui_->mainGLWidget->SetVertexesSize(arg1);
  settings_->setValue("Vertexes/Size", arg1);
}

void MainWindow::on_comboBoxFacesType_currentIndexChanged(int index) {
  ui_->mainGLWidget->SetFacesType((FacesType)index);
  settings_->setValue("Faces/Type", index);
}
void MainWindow::on_pushButtonSaveGIF_clicked() {
  ui_->pushButtonSaveGIF->setText("Recording");
  gif_ = new QGifImage;
  gif_->setDefaultDelay(100);
  gif_time_->start(100);
}

void MainWindow::createGIF() {
  if (gif_->frameCount() < 50) {
    QImage frame = ui_->mainGLWidget->grabFramebuffer();
    gif_->addFrame(frame.scaled(640, 480));
  } else {
    gif_time_->stop();
    ui_->pushButtonSaveGIF->setText("Save GIF");
    QString filename =
        QFileDialog::getSaveFileName(0, "Save GIF", QDir::homePath(), "*.gif");
    gif_->save(filename);
    delete gif_;
  }
}

void MainWindow::on_pushButtonSaveIMG_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      0, "Save IMG", QDir::homePath(), "*.png ;; *.jpg ;; *.bmp");
  ui_->mainGLWidget->grabFramebuffer().save(filename);
}

void MainWindow::on_pushButtonResetObj_clicked() {
  ui_->mainGLWidget->ResetObj();
}

}  // namespace s21
