#include "poppy.h"
#include <thread>

using std::cout;
using std::endl;
using namespace poppy;

int main() {
  // first,
  Initialize();

  // relative path
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("06_thread");

  // reserve function object
  auto func = module.GetAttribute("multiply").ToFunc();

  // acquire GIL context
  GILContext context;

  // this variable can be double-accessed without any mutex
  auto sum = 0;

  // launch sub-thread (1)
  std::thread th1([&context, &func, &sum]() {
    for (int i = 0; i < 1000; ++i) {
      // lock
      context.Lock();
      // run function
      sum += func(Int(4), Int(5)).ToValue().ToInt();
      // unlock
      context.Unlock();
    }
  });

  // launch sub-thread (2)
  std::thread th2([&context, &func, &sum]() {
    for (int i = 0; i < 1000; ++i) {
      // auto-lock
      context.Scope([&func, &sum]() {
        // run function
        sum += func(Int(2), Int(3)).ToValue().ToInt();
      });
    }
  });

  // wait
  th1.join();
  th2.join();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  cout << "Result of sum: " << sum << std::endl;
  
  // release GIL context
  context.Release();

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
