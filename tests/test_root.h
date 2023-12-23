#include "poppy.h"
#include "gtest/gtest.h"

using namespace poppy;

class Test : public testing::Test {
protected:
  Test() : module_(Init()) {}
  virtual ~Test() {
    Finalize();
  }
  static auto Init() -> Object {
    Initialize();
    AddModuleDirectory("tests");
    return Import("script");
  }
  Object module_;
};

class ThreadingTest : public testing::Test {
protected:
  ThreadingTest() : module_(Init()) {}
  virtual ~ThreadingTest() {
    context_.Release();
    Finalize();
  }
  static auto Init() -> Object {
    Initialize();
    AddModuleDirectory("tests");
    return Import("script");
  }
  Object module_;
  GILContext context_;
};
