#include "poppy.h"
#include <Python.h>

namespace poppy {

void Initialize() {
  if (!Py_IsInitialized()) {
    Py_Initialize();
    AddModuleDirectory(".");
  }
}

void Finalize() {
  Py_Finalize();
}

void AddModuleDirectory(const std::string& target_path) {
  auto sys = PyImport_ImportModule("sys");
  auto path = PyObject_GetAttrString(sys, "path");
  Py_DECREF(sys);
  auto str = PyUnicode_DecodeFSDefault(target_path.c_str());
  PyList_Append(path, str);
  Py_DECREF(path);
  Py_DECREF(str);
}

}