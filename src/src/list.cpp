#include "poppy.h"
#include <Python.h>

namespace poppy {

List::List(void* ptr) 
  : Object(ptr) {}

List::List(const std::vector<Object>& initializer)
  : Object(Init(initializer)) {}

auto List::Init(const std::vector<Object>& initializer) -> void* {
  auto list = PyList_New(initializer.size());
  int i = 0;
  for (const auto& item : initializer) {
    PyList_SetItem(list, i++, PYOBJ_REF(&item));
  }
  return list;
}

auto List::Set(const int& index, const Object& item) const -> void {
  if (PyList_SetItem(PYOBJ_REF(this), index, PYOBJ_REF(&item)) < 0) {
    throw std::out_of_range("");
  }
}

auto List::Get(const int& index) const -> Generic {
  auto obj = PyList_GetItem(PYOBJ_REF(this), index);
  if (!obj) {
    throw std::out_of_range("");
  }
  return Generic(obj);
}

auto List::Insert(const int& index, const Object& item) const -> void {
  if (index < 0 || index > PyList_Size(PYOBJ_REF(this))) {
    throw std::out_of_range("");
  }
  PyList_Insert(PYOBJ_REF(this), index, PYOBJ_REF(&item));
}

auto List::Append(const Object& item) const -> void {
  PyList_Append(PYOBJ_REF(this), PYOBJ_REF(&item));
}

auto List::Sort() const -> void {
  PyList_Sort(PYOBJ_REF(this));
}

auto List::Reverse() const -> void {
  PyList_Reverse(PYOBJ_REF(this));
}

auto List::Size() const -> size_t {
  return PyList_Size(PYOBJ_REF(this));
}

auto List::ToTuple() const -> Tuple {
  return Tuple(PyList_AsTuple(PYOBJ_REF(this)));
}

auto List::ToStdVector() const -> std::vector<Generic> {
  std::vector<Generic> v;
  for (int i = 0; i < Size(); ++i) {
    v.push_back(Get(i));
  }
  return v;
}

}
