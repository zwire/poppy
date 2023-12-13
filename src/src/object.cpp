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
  Py_DECREF(name);
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

auto Object::ContainsAttribute(const std::string& name) const -> bool {
  return PyObject_HasAttrString(PYOBJ_PTR(this), name.c_str());
}

auto Object::RemoveAttribute(const std::string& name) const -> bool {
  return PyObject_DelAttrString(PYOBJ_PTR(this), name.c_str());
}

auto Object::SetAttribute(const std::string& name, const Object& obj) const -> bool {
  return PyObject_SetAttrString(PYOBJ_PTR(this), name.c_str(), PYOBJ_PTR(&obj)) == 0;
}

auto Object::SetAttributes(const Dict& dict) const -> bool {
  return PyObject_GenericSetDict(PYOBJ_PTR(this), PYOBJ_PTR(&dict), NULL) == 0;
}

auto Object::GetAttribute(const std::string& name) const -> Generic {
  return Generic(PyObject_GetAttrString(PYOBJ_PTR(this), name.c_str()));
}

auto Object::GetAttributes() const -> Dict {
  return Dict(PyObject_GenericGetDict(PYOBJ_PTR(this), NULL));
}

}
