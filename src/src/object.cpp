#include "poppy.h"
#include <Python.h>

namespace poppy {

class ObjectImpl {
public:
  ObjectImpl(void* ptr)
    : ptr_(reinterpret_cast<PyObject*>(ptr)) {
    Py_INCREF(ptr_);
  }
  ObjectImpl(const ObjectImpl& obj)
    : ptr_(obj.ptr_) {
    Py_INCREF(ptr_);
  }
  ~ObjectImpl() {
    Py_DECREF(ptr_);
  }
  auto ObjectImpl::operator=(const ObjectImpl& obj) -> ObjectImpl& {
    Py_INCREF(ptr_);
    ptr_ = obj.ptr_;
  }
  auto ObjectImpl::GetAddress() const -> PyObject* {
    return ptr_;
  }
private:
  PyObject* ptr_;
};

Object::Object(void* ptr)
  : ref_(new int(0)), 
    pimpl_(new ObjectImpl(ptr)) {}

Object::Object(const Object& obj)
  : ref_(obj.ref_), 
    pimpl_(obj.pimpl_) {
  (*ref_)++;
}

auto Object::Load(const std::string& file_name) -> Object {
  auto name = PyUnicode_DecodeFSDefault(file_name.c_str());
  auto module = PyImport_Import(name);
  if (module) {
    return Object(module);
  } else {
    PyErr_Print();
    throw std::runtime_error("Failed to load module");
  }
}

Object::~Object() {
  if (*ref_ == 0) {
    delete pimpl_;
    delete ref_;
  } else {
    (*ref_)--;
  }
}

auto Object::operator=(const Object& obj) -> Object& {
  pimpl_ = obj.pimpl_;
  (*ref_)++;
  return *this;
}

auto Object::None() -> Object {
  return Object(Py_None);
}

auto Object::GetAddress() const -> void* {
  return pimpl_->GetAddress();
}

auto Object::Type() const -> std::string {
  auto obj = PyObject_Type(PYOBJ_PTR(this));
  auto type = PyObject_GetAttrString(obj, "__name__");
  Py_DECREF(obj);
  auto str = PyUnicode_AsUTF8(type);
  Py_DECREF(type);
  return str;
}

auto Object::IsNone() const -> bool {
  return pimpl_->GetAddress() == Py_None;
}

auto Object::IsValue() const -> bool {
  auto ptr = pimpl_->GetAddress();
  return
    PyBool_Check(ptr) ||
    PyLong_Check(ptr) ||
    PyFloat_Check(ptr) ||
    PyUnicode_Check(ptr) ||
    PyBytes_Check(ptr) ||
    PyByteArray_Check(ptr);
}

auto Object::IsTuple() const -> bool {
  return PyTuple_Check(pimpl_->GetAddress());
}

auto Object::IsList() const -> bool {
  return PyList_Check(pimpl_->GetAddress());
}

auto Object::IsDict() const -> bool {
  return PyDict_Check(pimpl_->GetAddress());
}

auto Object::IsBuffer() const -> bool {
  return PyObject_CheckBuffer(pimpl_->GetAddress());
}

auto Object::IsFunc() const -> bool {
  return PyCallable_Check(pimpl_->GetAddress());
}

auto Object::ToValue() const -> Value {
  if (IsValue()) {
    return Value(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::ToTuple() const -> Tuple {
  if (IsTuple()) {
    return Tuple(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::ToList() const -> List {
  if (IsList()) {
    return List(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::ToDict() const -> Dict {
  if (IsDict()) {
    return Dict(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::ToBuffer() const -> Buffer {
  if (IsBuffer()) {
    return Buffer(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::ToFunc() const -> Func {
  if (IsFunc()) {
    return Func(GetAddress());
  } else {
    throw std::bad_cast();
  }
}

auto Object::GetAttribute(const std::string& func_name) const -> Object {
  return Object(PyObject_GetAttrString(PYOBJ_PTR(this), func_name.c_str()));
}

auto Object::GetAttributes() const -> Dict {
  return Dict(PyObject_GenericGetDict(PYOBJ_PTR(this), NULL));
}

}
