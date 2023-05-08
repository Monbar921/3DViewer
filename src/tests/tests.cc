#include <gtest/gtest.h>

#include <cmath>

#include "controller.h"
#include "objmemento.h"
#include "viewercore.h"

using namespace s21;

TEST(ViewerTest, parsing_test_1) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
}

TEST(ViewerTest, parsing_test_2) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/NOFILE.obj");
  ASSERT_EQ(code, s21::ErrorsType::kErrOpen);
}

TEST(ViewerTest, parsing_test_3) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test2.obj");
  ASSERT_EQ(code, s21::ErrorsType::kErr3DFormat);
}

TEST(ViewerTest, parsing_test_4) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test3.obj");
  ASSERT_EQ(code, s21::ErrorsType::kErr3DFormat);
}

TEST(ViewerTest, parsing_test_5) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test4.obj");
  ASSERT_EQ(code, s21::ErrorsType::kErr3DFormat);
}

TEST(ViewerTest, affine_test_1) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  TransformData transform_data = {0, 0, 0, 360, 360, 360, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x, post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y, post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z, post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, affine_test_2) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  TransformData transform_data = {0, 0, 0, 180, 0, 0, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x, post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y, -post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z, -post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, affine_test_3) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  TransformData transform_data = {0, 0, 0, 0, 180, 0, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x, -post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y, post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z, -post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, affine_test_4) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  TransformData transform_data = {0, 0, 0, 0, 0, 180, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x, -post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y, -post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z, post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, affine_test_5) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  float delta_x = 3.56;
  float delta_y = -5.34;
  float delta_z = 8.12;
  TransformData transform_data = {delta_x, delta_y, delta_z, 0, 0, 0, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x + delta_x, post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y + delta_y, post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z + delta_z, post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, affine_test_6) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->faces_number, 4);
  ASSERT_EQ(controller.GetObjPtr()->edges_number, 12);
  ASSERT_EQ(controller.GetObjPtr()->all_faces_vertexes_number, 12);
  float init_first_x = controller.GetObjPtr()->vertexes_data[0];
  float init_first_y = controller.GetObjPtr()->vertexes_data[1];
  float init_first_z = controller.GetObjPtr()->vertexes_data[2];

  float delta_x = 3.56;
  float delta_y = -5.34;
  float delta_z = 8.12;
  TransformData transform_data = {delta_x, delta_y, delta_z, 180,
                                  180,     180,     1.0};
  controller.TransformateCoords(&transform_data);
  transform_data = (TransformData){-0, -0, -0, 360, 360, 360, 1.0};
  controller.TransformateCoords(&transform_data);
  float post_first_x = controller.GetObjPtr()->vertexes_data[0];
  float post_first_y = controller.GetObjPtr()->vertexes_data[1];
  float post_first_z = controller.GetObjPtr()->vertexes_data[2];

  ASSERT_NEAR(init_first_x, post_first_x, fabs(init_first_x * 0.01));
  ASSERT_NEAR(init_first_y, post_first_y, fabs(init_first_y * 0.01));
  ASSERT_NEAR(init_first_z, post_first_z, fabs(init_first_z * 0.01));
}

TEST(ViewerTest, memento_1) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  s21::common::ObjMemento memento(*controller.GetObjPtr());
  s21::common::ObjData obj = memento.GetState();
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, obj.vertexes_number);
}

TEST(ViewerTest, memento_2) {
  ViewerCore* viewerCore = ViewerCore::GetInstance();
  Controller controller(viewerCore);

  s21::ErrorsType code = controller.GetObjData("./tests/test1.obj");
  ASSERT_EQ(code, s21::ErrorsType::kSuccess);
  s21::common::ObjMemento memento(*controller.GetObjPtr());
  code = controller.GetObjData("./tests/test5.obj");
  memento.SetState(*controller.GetObjPtr());
  s21::common::ObjData obj = memento.GetState();
  ASSERT_EQ(controller.GetObjPtr()->vertexes_number, obj.vertexes_number);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
