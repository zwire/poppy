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
