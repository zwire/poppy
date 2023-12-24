#include "test_root.h"

TEST_F(Test, Tuple) {
  auto t0 = Tuple(std::vector<Object>{ Int(-1), Float(8), Str("hello") });
  EXPECT_EQ(3, t0.Size());
  EXPECT_EQ(-1, t0.Get(0).ToValue().ToInt());
  EXPECT_FLOAT_EQ(8, t0.Get(1).ToValue().ToFloat());
  EXPECT_STREQ("hello", t0.Get(2).ToValue().ToString().c_str());

  int i = 0;
  for (const auto& t : t0.ToStdVector()) {
    switch (i++) {
      case 0:
        EXPECT_EQ(-1, t.ToValue().ToInt());
        break;
      case 1:
        EXPECT_FLOAT_EQ(8, t.ToValue().ToFloat());
        break;
      case 2:
        EXPECT_STREQ("hello", t.ToValue().ToString().c_str());
        break;
    }
  }
  EXPECT_EQ(3, i);
}

TEST_F(Test, TupleAbnormal) {
  auto t0 = Tuple(std::vector<Object>{ Int(-1), Float(8), Str("hello") });

  try {
    auto t1 = t0.Get(-1);
    FAIL();
  }
  catch (std::out_of_range& e) {
    EXPECT_STREQ("", e.what());
  }
  catch (...) {
    FAIL();
  }
}
