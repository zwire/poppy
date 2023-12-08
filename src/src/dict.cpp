#include "poppy.h"
#include <Python.h>

namespace poppy {

Dict::Dict(void* ptr)
  : Object(ptr) {}

Dict::Dict(const Dict& obj)
  : Object(obj) {}

Dict::Dict(const std::map<std::string, Object>& initializer)
  : Object(Init(initializer)) {}

Dict::Dict(const std::map<Object, Object>& initializer)
  : Object(Init(initializer)) {}

auto Dict::Init(const std::map<std::string, Object>& initializer) -> void* {
  auto dict = PyDict_New();
  for (const auto& kv : initializer) {
    PyDict_SetItemString(dict, kv.first.c_str(), PYOBJ_PTR(&kv.second));
  }
  return dict;
}

auto Dict::Init(const std::map<Object, Object>& initializer) -> void* {
  auto dict = PyDict_New();
  for (const auto& kv : initializer) {
    PyDict_SetItem(dict, PYOBJ_PTR(&kv.first), PYOBJ_PTR(&kv.second));
  }
  return dict;
}

auto Dict::Set(const std::string& key, const Object& item) const -> void {
  PyDict_SetItemString(PYOBJ_PTR(this), key.c_str(), PYOBJ_PTR(&item));
}

auto Dict::Set(const Object& key, const Object& item) const -> void {
  PyDict_SetItem(PYOBJ_PTR(this), PYOBJ_PTR(&key), PYOBJ_PTR(&item));
}

auto Dict::Get(const std::string& key) const -> Object {
  return Object(PyDict_GetItemString(PYOBJ_PTR(this), key.c_str()));
}

auto Dict::Get(const Object& key) const -> Object {
  return Object(PyDict_GetItem(PYOBJ_PTR(this), PYOBJ_PTR(&key)));
}

auto Dict::Delete(const std::string& key) const -> void {
  PyDict_DelItemString(PYOBJ_PTR(this), key.c_str());
}

auto Dict::Delete(const Object& key) const -> void {
  PyDict_DelItem(PYOBJ_PTR(this), PYOBJ_PTR(&key));
}

auto Dict::Contains(const std::string& key) const -> bool {
  return PyDict_Contains(PYOBJ_PTR(this), PYOBJ_PTR(&Value::FromString(key)));
}

auto Dict::Contains(const Object& key) const -> bool {
  return PyDict_Contains(PYOBJ_PTR(this), PYOBJ_PTR(&key));
}

auto Dict::GetKeys() const -> List {
  return List(PyDict_Keys(PYOBJ_PTR(this)));
}

auto Dict::GetValues() const -> List {
  return List(PyDict_Values(PYOBJ_PTR(this)));
}

auto Dict::Size() const -> size_t {
  return PyDict_Size(PYOBJ_PTR(this));
}

}