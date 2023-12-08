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
  auto module = Import("01_echo");

  // reserve function object
  auto func = module.GetAttribute("echo").ToFunc();

  // run function
  auto tuple = func(Str("hello")).ToTuple();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  std::cout
    << "Reply: "
    << tuple.Get(0).ToValue().ToString() << ", "
    << tuple.Get(1).ToValue().ToString() << "!" << std::endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}