#include "poppy.h"
#include <Python.h>

namespace poppy {

Value::Value(void* ptr)
  : Object(ptr) {}

auto Value::True() -> Value {
  return Value(Py_True);
}

auto Value::False() -> Value {
  return Value(Py_False);
}

auto Value::FromBool(const bool& value) -> Value {
  return value ? True() : False();
}

auto Value::FromInt(const long& value) -> Value {
  return Value(PyLong_FromLong(value));
}

auto Value::FromFloat(const double& value) -> Value {
  return Value(PyFloat_FromDouble(value));
}

auto Value::FromString(const std::string& value) -> Value {
  return Value(PyUnicode_FromString(value.c_str()));
}

auto Value::FromBytes(const char* value, const size_t& size) -> Value {
  return Value(PyBytes_FromStringAndSize(value, size));
}

auto Value::FromBytes(const std::vector<char>& buf) -> Value {
  return Value::FromBytes(buf.data(), buf.size());
}

auto Value::FromByteArray(const char* value, const size_t& size) -> Value {
  return Value(PyByteArray_FromStringAndSize(value, size));
}

auto Value::FromByteArray(const std::vector<char>& buf) -> Value {
  return Value::FromBytes(buf.data(), buf.size());
}

auto Value::IsTrue() const -> bool {
  return PYOBJ_REF(this) == Py_True;
}

auto Value::IsFalse() const -> bool {
  return PYOBJ_REF(this) == Py_False;
}

auto Value::IsBool() const -> bool {
  return PyBool_Check(PYOBJ_REF(this));
}

auto Value::IsInt() const -> bool {
  return PyLong_Check(PYOBJ_REF(this));
}

auto Value::IsFloat() const -> bool {
  return PyFloat_Check(PYOBJ_REF(this)) || IsInt();
}

auto Value::IsString() const -> bool {
  return PyUnicode_Check(PYOBJ_REF(this));
}

auto Value::IsBytes() const -> bool {
  return PyBytes_Check(PYOBJ_REF(this));
}

auto Value::IsByteArray() const -> bool {
  return PyByteArray_Check(PYOBJ_REF(this));
}

auto Value::ToBool() const -> bool {
  if (IsBool()) {
    return PyBool_FromLong(ToInt());
  } else {
    throw std::bad_cast();
  }
}

auto Value::ToInt() const -> long {
  if (IsInt()) {
    return PyLong_AsLong(PYOBJ_REF(this));
  } else {
    throw std::bad_cast();
  }
}

auto Value::ToFloat() const -> double {
  if (IsFloat()) {
    return PyFloat_AsDouble(PYOBJ_REF(this));
  } else if (IsInt()) {
    return PyLong_AsDouble(PYOBJ_REF(this));
  } else {
    throw std::bad_cast();
  }
}

auto Value::ToString() const -> std::string {
  if (IsString()) {
    return std::string(PyUnicode_AsUTF8(PYOBJ_REF(this)));
  } else {
    throw std::bad_cast();
  }
}

auto Value::ToBytes() const -> std::vector<char> {
  if (IsBytes()) {
    auto ptr = PyBytes_AsString(PYOBJ_REF(this));
    auto size = PyBytes_Size(PYOBJ_REF(this));
    return std::vector<char>(ptr, ptr + size);
  } else {
    throw std::bad_cast();
  }  
}

auto Value::ToByteArray() const -> std::vector<char> {
  if (IsByteArray()) {
    auto ptr = PyByteArray_AsString(PYOBJ_REF(this));
    auto size = PyByteArray_Size(PYOBJ_REF(this));
    return std::vector<char>(ptr, ptr + size);
  } else {
    throw std::bad_cast();
  }  
}

}