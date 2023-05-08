#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H

#include "objdata.h"
#include "viewercore.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(ViewerCore *viewerCore);
  Controller() = delete;
  Controller(Controller &other) = delete;
  Controller(Controller &&other) = delete;
  void operator=(const Controller &) = delete;
  void operator=(const Controller &&) = delete;
  ErrorsType GetObjData(const std::string &filename);
  void TransformateCoords(TransformData *transform_data);
  ObjData *GetObjPtr();

 private:
  ViewerCore *viewerCore_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H
