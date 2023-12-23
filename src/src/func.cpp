#include "poppy.h"
#include <Python.h>

namespace poppy {

Func::Func(void* ptr)
  : Object(ptr) {}

auto Func::Invoke() const -> Generic {
  auto ret = PyObject_CallNoArgs(PYOBJ_REF(this));
  if (!ret) {
    throw std::runtime_error("failed to run function");
  }
  return Generic(ret);
}

auto Func::Invoke(const Object& arg) const -> Generic {
  auto ret = PyObject_CallOneArg(PYOBJ_REF(this), PYOBJ_REF(&arg));
  if (!ret) {
    throw std::runtime_error("failed to run function");
  }
  return Generic(ret);
}

auto Func::operator()() const -> Generic {
  return Invoke();
}

auto Func::operator()(const Object& arg) const -> Generic {
  return Invoke(arg);
}

auto Func::InvokeTuple(const Tuple& args) const -> Generic {
  auto ret = PyObject_CallObject(PYOBJ_REF(this), PYOBJ_REF(&args));
  if (!ret) {
    throw std::runtime_error("failed to run function");
  }
  return Generic(ret);
}

}
