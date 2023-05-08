#ifndef CPP4_3DVIEWER_V2_0_COMMON_OBJDATA_H
#define CPP4_3DVIEWER_V2_0_COMMON_OBJDATA_H

#include <vector>

#include "structs.h"

namespace s21::common {
struct ObjData {
  void ClearObjData();
  void ReAllocObjData();

  float scaled_with;
  float x_shifted;
  float y_shifted;
  float z_shifted;
  float x_rotated;
  float y_rotated;
  float z_rotated;

  unsigned vertexes_number;
  unsigned faces_number;
  unsigned all_faces_vertexes_number;
  unsigned edges_number;

  std::vector<float> vertexes_data;
  std::vector<unsigned> indexex_for_face;
  std::vector<unsigned> faces_data;
  std::vector<unsigned> edges_data;
};
}  // namespace s21::common

#endif  // CPP4_3DVIEWER_V2_0_COMMON_OBJDATA_H
