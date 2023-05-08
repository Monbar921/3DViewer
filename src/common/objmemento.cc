#include "objmemento.h"
namespace s21::common {

ObjMemento::ObjMemento(const ObjData& obj) : state_(obj) {}

ObjData ObjMemento::GetState() { return state_; }

void s21::common::ObjMemento::SetState(const ObjData& state) { state_ = state; }

}  // namespace s21::common
