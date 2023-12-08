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
