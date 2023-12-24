#include "test_root.h"

TEST_F(Test, List) {
  auto t0 = List(std::vector<Object>{ Int(-1), Float(8), Str("hello") });
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

  t0.Insert(0, Str("insert"));
  EXPECT_EQ(4, t0.Size());
  EXPECT_STREQ("insert", t0.Get(0).ToValue().ToString().c_str());
  EXPECT_EQ(-1, t0.Get(1).ToValue().ToInt());
  EXPECT_FLOAT_EQ(8, t0.Get(2).ToValue().ToFloat());
  EXPECT_STREQ("hello", t0.Get(3).ToValue().ToString().c_str());

  t0.Append(Str("append"));
  EXPECT_EQ(5, t0.Size());
  EXPECT_STREQ("insert", t0.Get(0).ToValue().ToString().c_str());
  EXPECT_EQ(-1, t0.Get(1).ToValue().ToInt());
  EXPECT_FLOAT_EQ(8, t0.Get(2).ToValue().ToFloat());
  EXPECT_STREQ("hello", t0.Get(3).ToValue().ToString().c_str());
  EXPECT_STREQ("append", t0.Get(4).ToValue().ToString().c_str());

  t0.Reverse();
  EXPECT_EQ(5, t0.Size());
  EXPECT_STREQ("append", t0.Get(0).ToValue().ToString().c_str());
  EXPECT_STREQ("hello", t0.Get(1).ToValue().ToString().c_str());
  EXPECT_FLOAT_EQ(8, t0.Get(2).ToValue().ToFloat());
  EXPECT_EQ(-1, t0.Get(3).ToValue().ToInt());
  EXPECT_STREQ("insert", t0.Get(4).ToValue().ToString().c_str());

  auto t1 = List();
  t1.Append(Int(-1));
  t1.Append(Int(5));
  t1.Append(Float(2.5));
  t1.Append(Int(2));
  t1.Sort();
  EXPECT_EQ(-1, t1.Get(0).ToValue().ToInt());
  EXPECT_EQ(2, t1.Get(1).ToValue().ToInt());
  EXPECT_FLOAT_EQ(2.5, t1.Get(2).ToValue().ToFloat());
  EXPECT_EQ(5, t1.Get(3).ToValue().ToInt());

  t1.Set(0, Str("set"));
  EXPECT_STREQ("set", t1.Get(0).ToValue().ToString().c_str());
}

TEST_F(Test, ListAbnormal) {
  auto t0 = List(std::vector<Object>{ Int(-1), Float(8), Str("hello") });

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

  try {
    t0.Insert(-1, Int(1));
    FAIL();
  }
  catch (std::out_of_range& e) {
    EXPECT_STREQ("", e.what());
  }
  catch (...) {
    FAIL();
  }

  try {
    t0.Set(-1, Int(1));
    FAIL();
  }
  catch (std::out_of_range& e) {
    EXPECT_STREQ("", e.what());
  }
  catch (...) {
    FAIL();
  }
}
