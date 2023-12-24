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
