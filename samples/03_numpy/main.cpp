#include "poppy.h"
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
    << "bytes / unit: " << val.BytesPerUnit() << endl
    << "dim: " << val.Dimensions() << endl;
  
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
