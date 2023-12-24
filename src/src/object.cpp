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
    ptr_ = obj.ptr_;
    Py_INCREF(ptr_);
    return *this;
  }
  auto ObjectImpl::GetRef() const -> PyObject* {
    return ptr_;
  }
private:
  PyObject* ptr_;
};

Object::Object()
  : ref_(new int(0)), 
    pimpl_(new ObjectImpl(Py_None)) {}

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
    pimpl_ = nullptr;
    delete ref_;
    ref_ = nullptr;
  } else {
    (*ref_)--;
  }
}

auto Object::operator=(const Object& obj) -> Object& {
  pimpl_ = obj.pimpl_;
  ref_ = obj.ref_;
  (*ref_)++;
  return *this;
}

auto Object::operator==(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_EQ);
}

auto Object::operator!=(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_NE);
}

auto Object::operator<(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_LT);
}

auto Object::operator<=(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_LE);
}

auto Object::operator>(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_GT);
}

auto Object::operator>=(const Object& obj) const -> bool {
  return PyObject_RichCompareBool(PYOBJ_REF(this), PYOBJ_REF(&obj), Py_GE);
}

auto operator<<(std::ostream& out, const Object& obj) -> std::ostream& {
  out << obj.ToString();
  return out;
}

auto Object::None() -> Object {
  return Object(Py_None);
}

auto Object::GetRef() const -> void* {
  return pimpl_->GetRef();
}

auto Object::Type() const -> std::string {
  auto obj = PyObject_Type(PYOBJ_REF(this));
  auto type = PyObject_GetAttrString(obj, "__name__");
  Py_DECREF(obj);
  auto str = PyUnicode_AsUTF8(type);
  Py_DECREF(type);
  return str;
}

auto Object::Hash() const -> size_t {
  return PyObject_Hash(PYOBJ_REF(this));
}

auto Object::ToString() const -> std::string {
  auto repr = PyObject_Repr(PYOBJ_REF(this));
  auto str = PyUnicode_AsUTF8(repr);
  Py_XDECREF(repr);
  return str;
}

auto Object::IsNone() const -> bool {
  return pimpl_->GetRef() == Py_None;
}

auto Object::ContainsAttribute(const std::string& name) const -> bool {
  return PyObject_HasAttrString(PYOBJ_REF(this), name.c_str());
}

auto Object::RemoveAttribute(const std::string& name) const -> bool {
  return PyObject_DelAttrString(PYOBJ_REF(this), name.c_str());
}

auto Object::SetAttribute(const std::string& name, const Object& obj) const -> bool {
  return PyObject_SetAttrString(PYOBJ_REF(this), name.c_str(), PYOBJ_REF(&obj)) == 0;
}

auto Object::SetAttributes(const Dict& dict) const -> bool {
  return PyObject_GenericSetDict(PYOBJ_REF(this), PYOBJ_REF(&dict), NULL) == 0;
}

auto Object::GetAttribute(const std::string& name) const -> Generic {
  return Generic(PyObject_GetAttrString(PYOBJ_REF(this), name.c_str()));
}

auto Object::GetAttributes() const -> Dict {
  return Dict(PyObject_GenericGetDict(PYOBJ_REF(this), NULL));
}

}
