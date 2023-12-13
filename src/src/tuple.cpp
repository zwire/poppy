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
    PyTuple_SetItem(tuple, i++, PYOBJ_PTR(&item));
  }
  return tuple;
}

auto Tuple::Set(const int& index, const Object& item) const -> void {
  PyTuple_SetItem(PYOBJ_PTR(this), index, PYOBJ_PTR(&item));
}

auto Tuple::Get(const int& index) const -> Generic {
  return Generic(PyTuple_GetItem(PYOBJ_PTR(this), index));
}

auto Tuple::Get(const int& start, const int& end) const -> Generic {
  return Generic(PyTuple_GetSlice(PYOBJ_PTR(this), start, end));
}

auto Tuple::Size() const -> size_t {
  return PyTuple_Size(PYOBJ_PTR(this));
}

}