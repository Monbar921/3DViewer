#ifndef CPP4_3DVIEWER_V2_0_MODEL_VIEWERCORE_H
#define CPP4_3DVIEWER_V2_0_MODEL_VIEWERCORE_H

#include <math.h>

#include <cstdio>
#include <string>

#include "objdata.h"
#include "structs.h"

namespace s21 {
using namespace common;
class ViewerCore {
 public:
  ErrorsType GetObjData(const std::string &filename);
  void TransformateCoords(TransformData *transform_data);
  ObjData *GetObjPtr();
  static ViewerCore *GetInstance() {
    if (instance_ == nullptr) {
      instance_ = new ViewerCore();
    }
    return instance_;
  }

 private:
  ViewerCore();
  ViewerCore(ViewerCore &other) = delete;
  ViewerCore(ViewerCore &&other) = delete;
  void operator=(const ViewerCore &) = delete;
  void operator=(const ViewerCore &&) = delete;
  ErrorsType FillObjData();
  ErrorsType CountUpObjData();
  void SkipLine();
  void RotateCoords(float *coord1, float *coord2, float angle);

  static ViewerCore *instance_;
  ObjData obj_data_;
  FILE *fp_ = nullptr;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_MODEL_VIEWERCORE_H
