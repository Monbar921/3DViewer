#include "gemmaglwidget.h"

namespace s21 {

GemmaGLWidget::GemmaGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  main_obj_ = nullptr;
  default_state_keeper_ = new ObjMemento(ObjData());
  ResetMainTransformData();
}

void GemmaGLWidget::ResetMainTransformData() {
  main_obj_scale_ = 1;
  main_obj_x_shift = 0;
  main_obj_y_shift = 0;
  main_obj_z_shift = 0;
  main_obj_x_angle = 0;
  main_obj_y_angle = 0;
  main_obj_z_angle = 0;
  FillMainTransformData();
}

void GemmaGLWidget::SetObjPtr(ObjData* obj_ptr) { main_obj_ = obj_ptr; }

void GemmaGLWidget::SetProjectionType(ProjectionType type) {
  projection_type_ = type;
  update();
}

void GemmaGLWidget::SetEdgesType(EdgesType type) {
  edges_type_ = type;
  update();
}

void GemmaGLWidget::SetEdgesColor(QColor color) {
  edges_color_r_ = color.redF();
  edges_color_g_ = color.greenF();
  edges_color_b_ = color.blueF();
  update();
}

void GemmaGLWidget::SetEdgesSize(unsigned size) {
  edges_size_ = size;
  update();
}

void GemmaGLWidget::SetVertexType(VertexType type) {
  vertexes_type_ = type;
  update();
}

void GemmaGLWidget::SetVertexesColor(QColor color) {
  vertexes_color_r_ = color.redF();
  vertexes_color_g_ = color.greenF();
  vertexes_color_b_ = color.blueF();
  update();
}

void GemmaGLWidget::SetVertexesSize(unsigned size) {
  vertexes_size_ = size;
  update();
}

void GemmaGLWidget::SetFacesType(FacesType type) {
  faces_type_ = type;
  update();
}

void GemmaGLWidget::SetFacesColor(QColor color) {
  faces_color_r_ = color.redF();
  faces_color_g_ = color.greenF();
  faces_color_b_ = color.blueF();
  update();
}

void GemmaGLWidget::SetBackGroundColor(QColor color) {
  bg_color_r_ = color.redF();
  bg_color_g_ = color.greenF();
  bg_color_b_ = color.blueF();
  update();
}

void GemmaGLWidget::ApplyTransformToObj() {
  if (main_obj_->vertexes_data.size()) {
    FillMainTransformData();
    controller_->TransformateCoords(&main_transform_data_);
    update();
  }
}

void GemmaGLWidget::FillMainTransformData() {
  main_transform_data_ = {main_obj_x_shift, main_obj_y_shift, main_obj_z_shift,
                          main_obj_x_angle, main_obj_y_angle, main_obj_z_angle,
                          main_obj_scale_};
}

void GemmaGLWidget::DefaultStateKeep() {
  default_state_keeper_->SetState(*main_obj_);
}

void GemmaGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glClearColor(1, 1, 1, 1.0);
}

void GemmaGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void GemmaGLWidget::paintGL() {
  glClearColor(bg_color_r_, bg_color_g_, bg_color_b_, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  if (projection_type_ == ProjectionType::kParallel) {
    glOrtho(-4.0, 4.0, -3.0, 3.0, -50.0, 50.0);
  } else {
    glFrustum(-1.0, 1.0, -0.75, 0.75, 1.0, 10000);
    glTranslated(0, 0, -5);
  }
  if (main_obj_->vertexes_data.size()) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &(main_obj_->vertexes_data.front()));
    if (vertexes_type_ != VertexType::kNone) {
      glColor3f(vertexes_color_r_, vertexes_color_g_, vertexes_color_b_);
      glPointSize(vertexes_size_);
      if (vertexes_type_ == VertexType::kRound) glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, main_obj_->vertexes_number);
      if (vertexes_type_ == VertexType::kRound) glDisable(GL_POINT_SMOOTH);
    }
  }
  if (main_obj_->edges_data.size()) {
    glColor3f(edges_color_r_, edges_color_g_, edges_color_b_);
    glLineWidth(edges_size_);
    if (edges_size_ != 1) glEnable(GL_LINE_SMOOTH);
    if (edges_type_ == EdgesType::kDotted) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    }
    glDrawElements(GL_LINES, main_obj_->edges_number * 2, GL_UNSIGNED_INT,
                   &(main_obj_->edges_data.front()));
    if (edges_type_ == EdgesType::kDotted) glDisable(GL_LINE_STIPPLE);
    if (edges_size_ > 1) glDisable(GL_LINE_SMOOTH);
  }
  if (main_obj_->faces_data.size()) {
    if (faces_type_ == FacesType::kSolid) {
      glColor3f(faces_color_r_, faces_color_g_, faces_color_b_);
      unsigned next = 0;
      for (int i = 0; i < main_obj_->faces_number; i++) {
        glDrawElements(GL_POLYGON, main_obj_->indexex_for_face[i],
                       GL_UNSIGNED_INT,
                       &(main_obj_->faces_data.front()) + next);
        next += main_obj_->indexex_for_face[i];
      }
    }
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GemmaGLWidget::mousePressEvent(QMouseEvent* event) {
  mouse_ptr_pos_ = event->position();
}

void GemmaGLWidget::mouseMoveEvent(QMouseEvent* event) {
  float delta_x = (event->position().x() - mouse_ptr_pos_.x()) / 100.0;
  float delta_y = -(event->position().y() - mouse_ptr_pos_.y()) / 100.0;
  Qt::MouseButtons button = event->buttons();
  if (button == Qt::RightButton) {
    delta_x /= 50.0;
    delta_y /= 50.0;
  }
  if (button == Qt::LeftButton) {
    main_obj_y_angle -= delta_x;
    if (main_obj_y_angle > 180) main_obj_y_angle = -180;
    if (main_obj_y_angle < -180) main_obj_y_angle = 180;
    main_obj_x_angle -= delta_y;
    if (main_obj_x_angle > 180) main_obj_x_angle = -180;
    if (main_obj_x_angle < -180) main_obj_x_angle = 180;
    emit mainObjRotated();
  } else if (button == Qt::RightButton) {
    main_obj_x_shift += delta_x;
    if (main_obj_x_shift > 100) main_obj_x_shift = 100;
    if (main_obj_x_shift < -100) main_obj_x_shift = -100;
    main_obj_y_shift += delta_y;
    if (main_obj_y_shift > 100) main_obj_y_shift = 100;
    if (main_obj_y_shift < -100) main_obj_y_shift = -100;
    emit mainObjShifted();
  }
  ApplyTransformToObj();
}

void GemmaGLWidget::wheelEvent(QWheelEvent* event) {
  main_obj_scale_ += event->angleDelta().y() / 10.0;
  if (main_obj_scale_ > 1000) main_obj_scale_ = 1000;
  if (main_obj_scale_ < -1000) main_obj_scale_ = -1000;
  ApplyTransformToObj();
  emit scaleChanged(main_obj_->scaled_with);
}

void GemmaGLWidget::ResetObj() {
  if (main_obj_->vertexes_data.size()) {
    *main_obj_ = default_state_keeper_->GetState();
    ResetMainTransformData();
    update();
    emit mainObjResetted();
  }
}

}  // namespace s21
