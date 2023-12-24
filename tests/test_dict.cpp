#include "test_root.h"

TEST_F(Test, Dict) {
  auto key0 = Int(0);
  auto key1 = Str("key1");

  std::unordered_map<Object, Object> map;
  map[key0] = Str("value0");
  map.insert(std::make_pair(key1, Int(1)));
  auto t0 = Dict(map);
  EXPECT_EQ(2, t0.Size());
  EXPECT_STREQ("value0", t0.Get(key0).ToValue().ToString().c_str());
  EXPECT_EQ(1, t0.Get(key1).ToValue().ToInt());

  t0 = Dict();
  t0.Set(key0, Str("value0"));
  t0.Set(key1, Int(1));
  t0.Set("key2", Tuple({ Int(-1), Float(0.5) }));

  EXPECT_EQ(3, t0.Size());
  EXPECT_STREQ("value0", t0.Get(key0).ToValue().ToString().c_str());
  EXPECT_EQ(1, t0.Get(key1).ToValue().ToInt());
  EXPECT_EQ(1, t0.Get("key1").ToValue().ToInt());
  auto t1 = t0.Get("key2").ToTuple();
  EXPECT_EQ(-1, t1.Get(0).ToValue().ToInt());
  EXPECT_FLOAT_EQ(0.5, t1.Get(1).ToValue().ToFloat());

  EXPECT_TRUE(t0.Contains(key0));
  EXPECT_FALSE(t0.Contains("0"));
  EXPECT_TRUE(t0.Contains("key1"));
  EXPECT_TRUE(t0.Contains(key1));
  EXPECT_TRUE(t0.Contains("key2"));
  EXPECT_FALSE(t0.Contains("key3"));

  int i = 0;
  for (const auto& t : t0.ToStdVector()) {
    switch (i++) {
      case 0:
        EXPECT_EQ(0, t.first.ToValue().ToInt());
        EXPECT_STREQ("value0", t.second.ToValue().ToString().c_str());
        break;
      case 1:
        EXPECT_STREQ("key1", t.first.ToValue().ToString().c_str());
        EXPECT_EQ(1, t.second.ToValue().ToInt());
        break;
      case 2:
        EXPECT_STREQ("key2", t.first.ToValue().ToString().c_str());
        EXPECT_EQ(-1, t.second.ToTuple().Get(0).ToValue().ToInt());
        EXPECT_FLOAT_EQ(0.5, t.second.ToTuple().Get(1).ToValue().ToFloat());
        break;
    }
  }
  EXPECT_EQ(3, i);

  i = 0;
  for (const auto& t : t0.GetKeys().ToStdVector()) {
    switch (i++) {
      case 0:
        EXPECT_EQ(0, t.ToValue().ToInt());
        break;
      case 1:
        EXPECT_STREQ("key1", t.ToValue().ToString().c_str());
        break;
      case 2:
        EXPECT_STREQ("key2", t.ToValue().ToString().c_str());
        break;
    }
  }

  i = 0;
  for (const auto& t : t0.GetValues().ToStdVector()) {
    switch (i++) {
      case 0:
        EXPECT_STREQ("value0", t.ToValue().ToString().c_str());
        break;
      case 1:
        EXPECT_EQ(1, t.ToValue().ToInt());
        break;
      case 2:
        EXPECT_EQ(-1, t.ToTuple().Get(0).ToValue().ToInt());
        EXPECT_FLOAT_EQ(0.5, t.ToTuple().Get(1).ToValue().ToFloat());
        break;
    }
  }

  t0.Delete("key1");
  EXPECT_FALSE(t0.Contains("key1"));

}

TEST_F(Test, DictAbnormal) {
  std::unordered_map<std::string, Object> map;
  map.insert(std::make_pair("key", Float(10)));
  auto t0 = Dict(map);

  try {
    auto t1 = t0.Get("?");
    FAIL();
  }
  catch (std::logic_error& e) {
    EXPECT_STREQ("not found", e.what());
  }
  catch (...) {
    FAIL();
  }

  try {
    auto t1 = t0.Get(Float(0.2));
    FAIL();
  }
  catch (std::logic_error& e) {
    EXPECT_STREQ("not found", e.what());
  }
  catch (...) {
    FAIL();
  }

  try {
    t0.Delete("hoge");
    FAIL();
  }
  catch (std::logic_error& e) {
    EXPECT_STREQ("not found", e.what());
  }
  catch (...) {
    FAIL();
  }

  try {
    t0.Delete(Int(-1));
    FAIL();
  }
  catch (std::logic_error& e) {
    EXPECT_STREQ("not found", e.what());
  }
  catch (...) {
    FAIL();
  }
}
