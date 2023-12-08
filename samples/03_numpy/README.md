### 03_numpy

This sample shows how to handle numpy data.
The C++ API can receive ndarray as Buffer object.
To send binary data without buffer copy, construct ndarray object from numpy module.
We provide ByteArray<T> struct so that you can create the ndarray object easily, as this example.

* Python code:
```py:03_numpy.py
import numpy as np

def c2py(mat: np.ndarray):
  print("------ C++ -> Python ------")
  print(mat)
  print()

def py2c() -> np.ndarray:
  mat = np.zeros((4, 7))
  mat[0, 0] = 0.1
  mat[0, 2] = 8
  mat[3, 2] = -2
  mat[1, 1] = 3.2
  mat[2, 3] = 0.3
  return mat
```

* C++ code:
```cpp:main.cpp
#include "poppy.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::abs;
using namespace poppy;

int main() {
  // first,
  Initialize();
  
  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("03_numpy");

  // load numpy module directly
  auto numpy = Import("numpy");

  // reserve function object
  auto c2py = module.GetAttribute("c2py").ToFunc();
  auto py2c = module.GetAttribute("py2c").ToFunc();

  // set arguments
  auto buf = ByteArray<double>(
    {
      1, 0, 0,
      2, 1, 0 
    }
  );

  // run function (1)
  auto ndarray =
    numpy
      .GetAttribute("frombuffer").ToFunc()(buf, Str("float64"))
      .GetAttribute("reshape").ToFunc()(Tuple(Int(2), Int(3)));
  c2py(ndarray);

  // run function (2)
  auto val = py2c().ToBuffer();
  auto shape = val.Shape();
  auto strides = val.Strides();
  
  // print results
  cout << "------ Python -> C++ ------" << endl;
  cout
    << "unit: " << val.UnitSize() << endl
    << "dim:  " << val.Dimensions() << endl;
  
  cout << "shape: [ ";
  for (const auto& s : shape) {
    cout << s << " ";
  }
  cout << "]" << endl;

  cout << "strides: [ ";
  for (const auto& s : strides) {
    cout << s << " ";
  }
  cout << "]" << endl;

  // print matrix
  auto data = val.Data<double>();
  cout << fixed << setprecision(1) << endl;
  for (int y = 0; y < shape[0]; ++y) {
    cout << "> ";
    for (int x = 0; x < shape[1]; ++x) {
      auto num = static_cast<double>(data[y * shape[1] + x]);
      cout << (num >= 0 ? "+" : "-") << abs(num) << "  ";
    }
    cout << endl;
  }

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
```

* Result:
```shell
------ C++ -> Python ------
[[1. 0. 0.]
 [2. 1. 0.]]

------ Python -> C++ ------
unit: 8
dim:  2
shape: [ 4 7 ]
strides: [ 56 8 ]

> +0.1  +0.0  +8.0  +0.0  +0.0  +0.0  +0.0
> +0.0  +3.2  +0.0  +0.0  +0.0  +0.0  +0.0
> +0.0  +0.0  +0.0  +0.3  +0.0  +0.0  +0.0
> +0.0  +0.0  -2.0  +0.0  +0.0  +0.0  +0.0
```
