#include "poppy.h"
#include <Python.h>

namespace poppy {

Tuple::Tuple(void* ptr)
  : Object(ptr) {}

Tuple::Tuple(const std::vector<Object>& initializer)
  : Object(Init(initializer)) {}

auto Tuple::Init(const std::vector<Object>& initializer) -> void* {
  auto tuple = PyTuple_New(initializer.size());
  int i = 0;
  for (const auto& item : initializer) {
    PyTuple_SetItem(tuple, i++, PYOBJ_REF(&item));
  }
  return tuple;
}

auto Tuple::Get(const int& index) const -> Generic {
  auto obj = PyTuple_GetItem(PYOBJ_REF(this), index);
  if (!obj) {
    throw std::out_of_range("");
  }
  return Generic(obj);
}

auto Tuple::Size() const -> size_t {
  return PyTuple_Size(PYOBJ_REF(this));
}

auto Tuple::ToStdVector() const -> std::vector<Generic> {
  std::vector<Generic> v;
  for (int i = 0; i < Size(); ++i) {
    v.push_back(Get(i));
  }
  return v;
}

}