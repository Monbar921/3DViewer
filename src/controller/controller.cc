#include "controller.h"

namespace s21 {

Controller::Controller(ViewerCore *viewerCore) { viewerCore_ = viewerCore; }

ErrorsType Controller::GetObjData(const std::string &filename) {
  return viewerCore_->GetObjData(filename);
}

void Controller::TransformateCoords(TransformData *transform_data) {
  viewerCore_->TransformateCoords(transform_data);
}

common::ObjData *Controller::GetObjPtr() { return viewerCore_->GetObjPtr(); }

}  // namespace s21