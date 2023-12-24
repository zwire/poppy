### 07_venv

You can use Python in virtual environment as well as the one installed in global environment.

First of all, create a new virtual environment.
```shell
python -m venv .venv
```

And activate it.
```shell
[windows]
.\.venv\Scripts\activate

[linux, mac]
. .venv/bin/activate
```

Then install some strange pip package. (not installed in global environment)
For example, we installed sympy.
```shell
pip install sympy
```

Sympy is a mathematical descriptor library.
Following exmaple shows how to use the library installed in virtual environment.

* Python code:
```py:07_venv.py
import sympy

def factor(formula: str) -> str:
  print("------ C++ -> Python ------")
  print(formula)
  print()
  expr = sympy.sympify(formula)
  return sympy.factor(expr)
```

* C++ code:
```cpp:main.cpp
#include "poppy.h"

using std::cout;
using std::endl;
using namespace poppy;

int main() {
  // first,
  Initialize(PYTHON_EXECUTABLE_PATH, PYTHON_MODULES_SEARCH_PATH);
  
  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("07_venv");

  // reserve function object
  auto func = module.GetAttribute("factor").ToFunc();

  // run function (factorization)
  auto ret = func(Str("x**2 + 2*x + 1"));

  // print result
  cout << "------ Python -> C++ ------" << endl;
  cout << ret << endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
```

* Result:
```shell
------ C++ -> Python ------
x**2 + 2*x + 1

------ Python -> C++ ------
(x + 1)**2
```
