#include "poppy.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using namespace poppy;

int main() {
  // first,
  Initialize();

  // relative path from workspace directory
  AddModuleDirectory("scripts");

  // load script file
  auto module = Import("06_thread");

  // reserve function object
  auto func = module.GetAttribute("multiply").ToFunc();

  // switch GIL context (acquire ownership),
  // this procedure must be conducted in the main thread
  auto context = GILContext::Acquire();

  // this variable can be double-accessed without any mutex
  auto sum = 0;

  // launch sub-thread (1)
  std::thread th1([&]() {
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
  std::thread th2([&]() {
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

  // switch GIL context (release ownership),
  // this procedure must be conducted in the main thread
  context.Release();

  // print results
  cout << "------ Python -> C++ ------" << endl;
  std::cout << "Result of sum: " << sum << std::endl;

  // after destructing all,
  Finalize();
  cout << "\n\n\n";
}
