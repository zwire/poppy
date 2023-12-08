#include "poppy.h"
#include <Python.h>

namespace poppy {

List::List(void* ptr) 
  : Object(ptr) {}

List::List(const List& obj)
  : Object(obj) {}

List::List(const std::vector<Object>& initializer)
  : Object(Init(initializer)) {}

auto List::Init(const std::vector<Object>& initializer) -> void* {
  auto list = PyList_New(initializer.size());
  int i = 0;
  for (const auto& item : initializer) {
    PyList_SetItem(list, i++, PYOBJ_PTR(&item));
  }
  return list;
}

auto List::Set(const int& index, const Object& item) const -> void {
  PyList_SetItem(PYOBJ_PTR(this), index, PYOBJ_PTR(&item));
}

auto List::Get(const int& index) const -> Object {
  return Object(PyList_GetItem(PYOBJ_PTR(this), index));
}

auto List::Get(const int& start, const int& end) const -> List {
  return List(PyList_GetSlice(PYOBJ_PTR(this), start, end));
}

auto List::Insert(const int& index, const Object& item) const -> void {
  PyList_Insert(PYOBJ_PTR(this), index, PYOBJ_PTR(&item));
}

auto List::Append(const Object& item) const -> void {
  PyList_Append(PYOBJ_PTR(this), PYOBJ_PTR(&item));
}

auto List::Sort() const -> void {
  PyList_Sort(PYOBJ_PTR(this));
}

auto List::Reverse() const -> void {
  PyList_Reverse(PYOBJ_PTR(this));
}

auto List::Size() const -> size_t {
  return PyList_Size(PYOBJ_PTR(this));
}

auto List::ToTuple() const -> Tuple {
  return Tuple(PyList_AsTuple(PYOBJ_PTR(this)));
}

}
