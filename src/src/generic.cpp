#include "poppy.h"
#include <Python.h>

namespace poppy {

Generic::Generic(void* ptr)
  : Object(ptr) {}

auto Generic::IsValue() const -> bool {
  auto ptr = GetAddress();
  return
    PyBool_Check(ptr) ||
    PyLong_Check(ptr) ||
    PyFloat_Check(ptr) ||
    PyUnicode_Check(ptr) ||
    PyBytes_Check(ptr) ||
    PyByteArray_Check(ptr);
}

auto Generic::IsTuple() const -> bool {
  return PyTuple_Check(GetAddress());
}

auto Generic::IsList() const -> bool {
  return PyList_Check(GetAddress());
}

auto Generic::IsDict() const -> bool {
  return PyDict_Check(GetAddress());
}

auto Generic::IsBuffer() const -> bool {
  return PyObject_CheckBuffer(PYOBJ_PTR(this));
}

auto Generic::IsFunc() const -> bool {
  return PyCallable_Check(PYOBJ_PTR(this));
}

auto Generic::ToValue() const -> Value {
  if (IsValue()) {
    return Value(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Generic::ToTuple() const -> Tuple {
  if (IsTuple()) {
    return Tuple(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Generic::ToList() const -> List {
  if (IsList()) {
    return List(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Generic::ToDict() const -> Dict {
  if (IsDict()) {
    return Dict(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Generic::ToBuffer() const -> Buffer {
  if (IsBuffer()) {
    return Buffer(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Generic::ToFunc() const -> Func {
  if (IsFunc()) {
    return Func(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

}
