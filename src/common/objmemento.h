#ifndef CPP4_3DVIEWER_V2_0_COMMON_OBJMEMENTO_H
#define CPP4_3DVIEWER_V2_0_COMMON_OBJMEMENTO_H

#include "objdata.h"
#include "structs.h"

namespace s21::common {
class ObjMemento {
 public:
  explicit ObjMemento(const ObjData &obj);
  ObjMemento() = delete;
  ObjMemento(ObjMemento &other) = delete;
  ObjMemento(ObjMemento &&other) = delete;
  void operator=(const ObjMemento &&) = delete;

  ObjData GetState();
  void SetState(const ObjData &state);

 private:
  ObjData state_;
};
}  // namespace s21::common

#endif  // CPP4_3DVIEWER_V2_0_COMMON_OBJMEMENTO_H
