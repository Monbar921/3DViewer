#ifndef CPP4_3DVIEWER_V2_0_COMMON_STRUCTS_H
#define CPP4_3DVIEWER_V2_0_COMMON_STRUCTS_H

namespace s21::common {

enum class ErrorsType { kSuccess = 0, kErrOpen, kErr3DFormat };

static constexpr float MY_PI = 3.14159265358979323846f;

struct TransformData {
  float x_shift;
  float y_shift;
  float z_shift;
  float x_angle;
  float y_angle;
  float z_angle;
  float scale_factor;
};

}  // namespace s21::common

#endif  // CPP4_3DVIEWER_V2_0_COMMON_STRUCTS_H
