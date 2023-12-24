### 02_calc

This sample shows how to do something like
[the official tutorial](https://docs.python.org/3/extending/embedding.html#pure-embedding).

* Python code:
```py:02_calc.py
def multiply(a: int, b: int) -> int:
  print("------ C++ -> Python ------")
  print("Will compute", a, "times", b)
  print()
  c = 0
  for i in range(0, a):
    c = c + b
  return c
```

* C++ code:
```cpp:main.cpp
#include "poppy.h"

using std::cout;
using std::endl;
using namespace poppy;

int main() {
  // first,
  Initialize();
  
  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("02_calc");

  // reserve function object
  auto func = module.GetAttribute("multiply").ToFunc();

  // run function
  auto val = func(Int(2), Int(3)).ToValue();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  std::cout << "Result of call: " << val.ToInt() << std::endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
```

* Result:
```shell
------ C++ -> Python ------
Will compute 2 times 3

------ Python -> C++ ------
Result of call: 6
```
