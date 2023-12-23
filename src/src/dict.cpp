#include "poppy.h"
#include <Python.h>

namespace poppy {

Dict::Dict(void* ptr)
  : Object(ptr) {}

Dict::Dict()
  : Object(Init(std::unordered_map<std::string, Object>())) {}

Dict::Dict(const std::unordered_map<std::string, Object>& initializer)
  : Object(Init(initializer)) {}

auto Dict::Init(const std::unordered_map<std::string, Object>& initializer) -> void* {
  auto dict = PyDict_New();
  for (const auto& kv : initializer) {
    PyDict_SetItemString(dict, kv.first.c_str(), PYOBJ_REF(&kv.second));
  }
  return dict;
}

auto Dict::Set(const std::string& key, const Object& item) const -> void {
  PyDict_SetItemString(PYOBJ_REF(this), key.c_str(), PYOBJ_REF(&item));
}

auto Dict::Set(const Object& key, const Object& item) const -> void {
  PyDict_SetItem(PYOBJ_REF(this), PYOBJ_REF(&key), PYOBJ_REF(&item));
}

auto Dict::Get(const std::string& key) const -> Generic {
  if (!Contains(key)) {
    throw std::logic_error("not found");
  }
  return Generic(PyDict_GetItemString(PYOBJ_REF(this), key.c_str()));
}

auto Dict::Get(const Object& key) const -> Generic {
  if (!Contains(key)) {
    throw std::logic_error("not found");
  }
  return Generic(PyDict_GetItem(PYOBJ_REF(this), PYOBJ_REF(&key)));
}

auto Dict::Delete(const std::string& key) const -> void {
  if (!Contains(key)) {
    throw std::logic_error("not found");
  }
  PyDict_DelItemString(PYOBJ_REF(this), key.c_str());
}

auto Dict::Delete(const Object& key) const -> void {
  if (!Contains(key)) {
    throw std::logic_error("not found");
  }
  PyDict_DelItem(PYOBJ_REF(this), PYOBJ_REF(&key));
}

auto Dict::Contains(const std::string& key) const -> bool {
  return PyDict_Contains(PYOBJ_REF(this), PYOBJ_REF(&Value::FromString(key)));
}

auto Dict::Contains(const Object& key) const -> bool {
  return PyDict_Contains(PYOBJ_REF(this), PYOBJ_REF(&key));
}

auto Dict::GetKeys() const -> List {
  return List(PyDict_Keys(PYOBJ_REF(this)));
}

auto Dict::GetValues() const -> List {
  return List(PyDict_Values(PYOBJ_REF(this)));
}

auto Dict::Size() const -> size_t {
  return PyDict_Size(PYOBJ_REF(this));
}

auto Dict::ToStdVector() const -> std::vector<std::pair<Generic, Generic>> {
  auto keys = GetKeys().ToStdVector();
  std::vector<std::pair<Generic, Generic>> v;
  for (const auto& key : keys) {
    auto pair = std::make_pair(key, Get(key));
    v.push_back(pair);
  }
  return v;
}

}