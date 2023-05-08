#ifndef CPP4_3DVIEWER_V2_0_VIEW_GEMMAGLWIDGET_H
#define CPP4_3DVIEWER_V2_0_VIEW_GEMMAGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "controller.h"
#include "objdata.h"
#include "objmemento.h"
#include "structs.h"

namespace s21 {

typedef enum class ProjectionType { kParallel, kCentral } ProjectionType;
typedef enum class EdgesType { kSolid, kDotted } EdgesType;
typedef enum class VertexType { kNone, kRound, kSquare } VertexType;
typedef enum class FacesType { kNone, kSolid } FacesType;

class GemmaGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

  friend class MainWindow;

 public:
  GemmaGLWidget(QWidget* parent = nullptr);

  void SetObjPtr(ObjData* obj_ptr);

  void SetProjectionType(ProjectionType type);

  void SetEdgesType(EdgesType type);
  void SetEdgesColor(QColor color);
  void SetEdgesSize(unsigned size);

  void SetVertexType(VertexType type);
  void SetVertexesColor(QColor color);
  void SetVertexesSize(unsigned size);

  void SetFacesType(FacesType type);
  void SetFacesColor(QColor color);

  void SetBackGroundColor(QColor color);

  void ApplyTransformToObj();
  void FillMainTransformData();

  void DefaultStateKeep();
  void ResetObj();
 signals:
  void scaleChanged(float new_scale);
  void mainObjShifted();
  void mainObjRotated();
  void mainObjResetted();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

 private:
  void ResetMainTransformData();
  ObjData* main_obj_;
  TransformData main_transform_data_;
  common::ObjMemento* default_state_keeper_ = nullptr;
  float main_obj_scale_;
  float main_obj_x_shift;
  float main_obj_y_shift;
  float main_obj_z_shift;
  float main_obj_x_angle;
  float main_obj_y_angle;
  float main_obj_z_angle;
  Controller* controller_ = nullptr;

  ProjectionType projection_type_;

  EdgesType edges_type_;
  float edges_color_r_ = 1;
  float edges_color_g_ = 1;
  float edges_color_b_ = 1;
  unsigned edges_size_ = 1;

  VertexType vertexes_type_;
  float vertexes_color_r_ = 1;
  float vertexes_color_g_ = 1;
  float vertexes_color_b_ = 1;
  unsigned vertexes_size_ = 1;

  FacesType faces_type_;
  float faces_color_r_ = 1;
  float faces_color_g_ = 1;
  float faces_color_b_ = 1;

  float bg_color_r_ = 0;
  float bg_color_g_ = 0.5;
  float bg_color_b_ = 0.5;

  QPointF mouse_ptr_pos_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_VIEW_GEMMAGLWIDGET_H
