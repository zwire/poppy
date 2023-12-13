#include "poppy.h"
#include <Python.h>

namespace poppy {

Func::Func(void* ptr)
  : Object(ptr) {}

auto Func::Invoke() const -> Generic {
  return Generic(PyObject_CallNoArgs(PYOBJ_PTR(this)));
}

auto Func::Invoke(const Object& arg) const -> Generic {
  return Generic(PyObject_CallOneArg(PYOBJ_PTR(this), PYOBJ_PTR(&arg)));
}

auto Func::operator()() const -> Generic {
  return Invoke();
}

auto Func::operator()(const Object& arg) const -> Generic {
  return Invoke(arg);
}

auto Func::InvokeTuple(const Tuple& args) const -> Generic {
  return Generic(PyObject_CallObject(PYOBJ_PTR(this), PYOBJ_PTR(&args)));
}

}
