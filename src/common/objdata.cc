#include "objdata.h"
namespace s21::common {

void ObjData::ReAllocObjData() {
  if (vertexes_number > 0) vertexes_data.resize(vertexes_number * 3);
  if (faces_number > 0) indexex_for_face.resize(faces_number);
  if (all_faces_vertexes_number > 0)
    faces_data.resize(all_faces_vertexes_number);
  if (edges_number > 0) edges_data.resize(edges_number * 2);
}

// ObjData::~ObjData() { ClearObjData(); }

void ObjData::ClearObjData() {
  scaled_with = 1.0;
  x_shifted = 0;
  y_shifted = 0;
  z_shifted = 0;
  x_rotated = 0;
  y_rotated = 0;
  z_rotated = 0;
  vertexes_number = 0;
  vertexes_data.clear();
  faces_number = 0;
  all_faces_vertexes_number = 0;
  indexex_for_face.clear();
  faces_data.clear();
  edges_number = 0;
  edges_data.clear();
}

}  // namespace s21::common