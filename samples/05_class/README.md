### 05_class

This sample shows how to instance a Python class and call its class method.

* Python code:
```py:05_class.py
from random import *

class Hoge:
  def __init__(self) -> None:
    self.seed = uniform(0, 1)
    pass

  def get(self) -> float:
    return self.seed * uniform(-1, 1)
  
  def set(self, val) -> None:
    self.seed = val
    print("------ C++ -> Python ------")
    print(f"set value: {val}")
    print()

def new() -> Hoge:
  return Hoge()
```

* C++ code:
```cpp:main.cpp
#include "poppy.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace poppy;

int main() {
  // first,
  Initialize();

  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("05_class");

  // instance class object
  auto hoge = module.GetAttribute("new").ToFunc()();

  // get class method
  auto get = hoge.GetAttribute("get").ToFunc();
  auto set = hoge.GetAttribute("set").ToFunc();

  // run function (1)
  set(Int(500));

  // run function (2)
  auto val = get().ToValue();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  cout << "get value: " << val.ToFloat() << endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
```

* Result:
```shell
------ C++ -> Python ------
set value: 500

------ Python -> C++ ------
get value: 495.261
```
