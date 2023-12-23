#include "test_root.h"

TEST_F(Test, Echo) {
  auto args = Tuple(Int(0), Str("hello"), Float(12.5));
  auto module = Import("script");
  auto func = module.GetAttribute("echo").ToFunc();
  auto ret = func.Invoke(args).ToTuple();
  EXPECT_EQ(0, ret.Get(0).ToValue().ToInt());
  EXPECT_STREQ("hello", ret.Get(1).ToValue().ToString().c_str());
  EXPECT_FLOAT_EQ(12.5, ret.Get(2).ToValue().ToFloat());
}

TEST_F(Test, EchoAbnormal) {
  auto args = Tuple(Int(0), Str("hello"), Float(12.5));
  auto module = Import("script");
  auto func = module.GetAttribute("echo_fail").ToFunc();
  try {
    auto ret = func.Invoke(args);
  }
  catch (std::runtime_error& e) {
    EXPECT_STREQ("failed to run function", e.what());
  }
}