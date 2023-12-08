### 04_struct

This sample shows how to receive a struct defined by Python ctypes.
Sending custom structures directly from C++ to Python is currently not implemented because it is quite complicated.

* Python code:
```py:04_struct.py
from ctypes import *
from random import *

class Child(Structure):
  _fields_ = [
    ('val0', c_double),
    ('val1', c_char * 32),
  ]

class Parent(Structure):
  _fields_ = [
    ('val0', c_int32),
    ('val1', Child * 4),
  ]

def py2c():
  p = Parent(int(uniform(-10, 10)))
  for i in range(3):
    p.val1[i] = Child(uniform(-10, 10), f"random: {random()}".encode("utf-8"))
  return p
```

* C++ code:
```cpp:main.cpp
#include "poppy.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace poppy;

struct Child {
  double val0;
  char val1[32];
};

struct Parent {
  int val0;
  Child val1[4];
};

int main() {
  // first,
  Initialize();

  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("04_struct");

  // reserve function object
  auto py2c = module.GetAttribute("py2c").ToFunc();

  // run function
  auto buf = py2c().ToBuffer();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  auto parent = reinterpret_cast<Parent*>(buf.Data());
  cout << "Parent: {" << endl;
  cout << "  val0: " << parent->val0 << "," << endl;
  cout << "  val1: [" << endl;
  for (int i = 0; i < 4; ++i) {
    auto child = parent->val1[i];
    cout << "    Child: {" << endl;
    cout << "      val0: " << child.val0 << "," << endl;
    cout << "      val1: " << child.val1 <<  endl;
    cout << "    }," << endl;
  }
  cout << "  ]," << endl;
  cout << "}" << endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
```

* Result:
```shell
------ Python -> C++ ------
Parent: {
  val0: -1,
  val1: [
    Child: {
      val0: -7.79611,
      val1: random: 0.7862637572587672
    },
    Child: {
      val0: 6.82853,
      val1: random: 0.07343110292224664
    },
    Child: {
      val0: -7.3038,
      val1: random: 0.5234234136800473
    },
    Child: {
      val0: 0,
      val1:
    },
  ],
}
```
