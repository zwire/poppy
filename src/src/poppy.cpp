#include "poppy.h"
#include <Python.h>

namespace poppy {

auto Initialize() -> void {
  if (!Py_IsInitialized()) {
    Py_Initialize();
    AddModuleDirectory(".");
  }
}

auto Initialize(
  const std::wstring& executable_path, 
  const std::wstring& module_search_path) -> void {
  if (!Py_IsInitialized()) {
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    PyConfig_Read(&config);
    config.module_search_paths_set = 1;
    PyWideStringList_Append(
      &config.module_search_paths, module_search_path.c_str());
    PyConfig_SetString(
      &config, &config.executable, executable_path.c_str());
    Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);
  }
}

auto Finalize() -> void {
  Py_Finalize();
}

auto AddModuleDirectory(const std::string& target_path) -> void {
  auto sys = PyImport_ImportModule("sys");
  auto path = PyObject_GetAttrString(sys, "path");
  Py_DECREF(sys);
  auto str = PyUnicode_DecodeFSDefault(target_path.c_str());
  PyList_Append(path, str);
  Py_DECREF(path);
  Py_DECREF(str);
}

}