#include "poppy.h"
#include "gtest/gtest.h"

using namespace poppy;

class Test : public testing::Test {
protected:
  Test() : module_(Init()) {}
  virtual ~Test() { Finalize(); }
  static auto Init() -> Object {
    Initialize();
    return Import("script");
  }
  Object module_;
};
