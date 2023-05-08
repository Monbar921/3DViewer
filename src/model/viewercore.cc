#include "viewercore.h"
namespace s21 {
using namespace common;

ViewerCore *ViewerCore::instance_ = nullptr;

ViewerCore::ViewerCore() {}

ErrorsType ViewerCore::GetObjData(const std::string &filename) {
  ErrorsType err_code;
  fp_ = std::fopen(filename.c_str(), "r");
  if (fp_) {
    err_code = CountUpObjData();
    if (err_code == ErrorsType::kSuccess) {
      obj_data_.ReAllocObjData();
      err_code = FillObjData();
    }
    std::fclose(fp_);
  } else {
    err_code = ErrorsType::kErrOpen;
  }
  return err_code;
}

ErrorsType ViewerCore::CountUpObjData() {
  ErrorsType err_code = ErrorsType::kSuccess;
  obj_data_.ClearObjData();
  std::rewind(fp_);
  while (!std::feof(fp_) && err_code == ErrorsType::kSuccess) {
    int tmp_chr = std::fgetc(fp_);
    if (tmp_chr == 'v') {
      if (std::fgetc(fp_) == ' ') obj_data_.vertexes_number++;
      SkipLine();
    } else if (tmp_chr == 'f') {
      if (std::fgetc(fp_) == ' ') {
        obj_data_.faces_number++;
        unsigned tmp_num, tmp_count = 0;
        while (std::fscanf(fp_, "%u%*[^ \n]", &tmp_num) == 1) {
          tmp_count++;
          obj_data_.all_faces_vertexes_number++;
          if (tmp_num > obj_data_.vertexes_number || tmp_num < 1)
            err_code = ErrorsType::kErr3DFormat;
        }
        obj_data_.edges_number += (tmp_count > 2 ? tmp_count : 1);
      } else {
        SkipLine();
      }
    } else {
      SkipLine();
    }
  }
  return err_code;
}

void ViewerCore::SkipLine() {
  std::fscanf(fp_, "%*[^\n]");
  std::fscanf(fp_, "%*[\n]");
}

ErrorsType ViewerCore::FillObjData() {
  ErrorsType err_code = ErrorsType::kSuccess;
  std::rewind(fp_);
  auto v_it = obj_data_.vertexes_data.begin();
  auto f_it = obj_data_.faces_data.begin();
  auto i_it = obj_data_.indexex_for_face.begin();
  auto e_it = obj_data_.edges_data.begin();
  while (!std::feof(fp_) && err_code == ErrorsType::kSuccess) {
    int tmp_chr = std::fgetc(fp_);
    if (tmp_chr == 'v') {
      if (std::fgetc(fp_) == ' ') {
        for (int i = 0; i < 3 && err_code == ErrorsType::kSuccess; i++) {
          if (std::fscanf(fp_, "%f", &*(v_it + i)) != 1)
            err_code = ErrorsType::kErr3DFormat;
        }
        v_it += 3;
      }
      SkipLine();
    } else if (tmp_chr == 'f') {
      if (std::fgetc(fp_) == ' ') {
        int indexex_count = 0;
        unsigned tmp_num, first_index;
        while (std::fscanf(fp_, "%u%*[^ \n]", &tmp_num) == 1) {
          *f_it++ = tmp_num - 1;
          indexex_count++;
          if (indexex_count == 1) first_index = tmp_num - 1;
          if (indexex_count > 2) {
            *e_it = *(e_it - 1);
            e_it++;
          }
          *e_it++ = tmp_num - 1;
        }
        if (indexex_count == 1) *e_it++ = first_index;
        if (indexex_count > 2) {
          *e_it = *(e_it - 1);
          e_it++;
          *e_it++ = first_index;
        }
        *i_it++ = indexex_count;
      } else {
        SkipLine();
      }
    } else {
      SkipLine();
    }
  }
  return err_code;
}

void ViewerCore::TransformateCoords(TransformData *transform_data) {
  float new_scale = pow(10, transform_data->scale_factor * 3.0 / 1000.0);
  float scale_coeff = new_scale / obj_data_.scaled_with;
  float alpha = (transform_data->x_angle - obj_data_.x_rotated) * MY_PI / 180.0;
  float beta = (transform_data->y_angle - obj_data_.y_rotated) * MY_PI / 180.0;
  float gamma = (transform_data->z_angle - obj_data_.z_rotated) * MY_PI / 180.0;
  for (unsigned i = 0; i < obj_data_.vertexes_number; i++) {
    obj_data_.vertexes_data[3 * i] -= obj_data_.x_shifted;
    obj_data_.vertexes_data[3 * i + 1] -= obj_data_.y_shifted;
    obj_data_.vertexes_data[3 * i + 2] -= obj_data_.z_shifted;
    RotateCoords(&obj_data_.vertexes_data[3 * i + 1],
                 &obj_data_.vertexes_data[3 * i + 2], alpha);
    RotateCoords(&obj_data_.vertexes_data[3 * i],
                 &obj_data_.vertexes_data[3 * i + 2], beta);
    RotateCoords(&obj_data_.vertexes_data[3 * i],
                 &obj_data_.vertexes_data[3 * i + 1], gamma);
    obj_data_.vertexes_data[3 * i] =
        scale_coeff * obj_data_.vertexes_data[3 * i] + transform_data->x_shift;
    obj_data_.vertexes_data[3 * i + 1] =
        scale_coeff * obj_data_.vertexes_data[3 * i + 1] +
        transform_data->y_shift;
    obj_data_.vertexes_data[3 * i + 2] =
        scale_coeff * obj_data_.vertexes_data[3 * i + 2] +
        transform_data->z_shift;
  }
  obj_data_.scaled_with = new_scale;
  obj_data_.x_shifted = transform_data->x_shift;
  obj_data_.y_shifted = transform_data->y_shift;
  obj_data_.z_shifted = transform_data->z_shift;
  obj_data_.x_rotated = transform_data->x_angle;
  obj_data_.y_rotated = transform_data->y_angle;
  obj_data_.z_rotated = transform_data->z_angle;
}

ObjData *ViewerCore::GetObjPtr() { return &obj_data_; }

void ViewerCore::RotateCoords(float *coord1, float *coord2, float angle) {
  float tmp1 = *coord1;
  float tmp2 = *coord2;
  *coord1 = cos(angle) * tmp1 - sin(angle) * tmp2;
  *coord2 = sin(angle) * tmp1 + cos(angle) * tmp2;
}

}  // namespace s21
