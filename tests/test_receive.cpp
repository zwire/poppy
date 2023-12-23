#include "test_root.h"

TEST_F(Test, Receive) {
  auto module = Import("script");

  auto buff = module.GetAttribute("make_buffer").ToFunc()().ToBuffer();
  EXPECT_EQ(6 * 4, buff.Length());
  EXPECT_EQ(2, buff.Dimensions());
  EXPECT_EQ(2, buff.Shape()[0]);
  EXPECT_EQ(3, buff.Shape()[1]);
  EXPECT_EQ(4, buff.BytesPerUnit());
  EXPECT_FLOAT_EQ(1, buff.Data<float>()[0]);
  EXPECT_FLOAT_EQ(0, buff.Data<float>()[1]);
  EXPECT_FLOAT_EQ(0, buff.Data<float>()[2]);
  EXPECT_FLOAT_EQ(0, buff.Data<float>()[3]);
  EXPECT_FLOAT_EQ(1, buff.Data<float>()[4]);
  EXPECT_FLOAT_EQ(0, buff.Data<float>()[5]);

  auto tuple = module.GetAttribute("make_tuple").ToFunc()().ToTuple();
  EXPECT_EQ(3, tuple.Size());
  EXPECT_STREQ("str", tuple.Get(0).ToValue().ToString().c_str());
  EXPECT_EQ(10, tuple.Get(1).ToValue().ToInt());
  EXPECT_FLOAT_EQ(0.1, tuple.Get(2).ToValue().ToFloat());

  auto list = module.GetAttribute("make_list").ToFunc()().ToList();
  EXPECT_EQ(3, list.Size());
  EXPECT_STREQ("str", list.Get(0).ToValue().ToString().c_str());
  EXPECT_EQ(10, list.Get(1).ToValue().ToInt());
  EXPECT_FLOAT_EQ(0.1, list.Get(2).ToValue().ToFloat());

  auto dict = module.GetAttribute("make_dict").ToFunc()().ToDict();
  EXPECT_EQ(3, dict.Size());
  EXPECT_STREQ("str", dict.Get(Int(0)).ToValue().ToString().c_str());
  EXPECT_EQ(10, dict.Get(Float(1.0)).ToValue().ToInt());
  EXPECT_FLOAT_EQ(0.1, dict.Get("key2").ToValue().ToFloat());
}
