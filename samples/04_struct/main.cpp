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
