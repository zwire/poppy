#include "test_root.h"

TEST_F(Test, CastToBool) {
  // check type name
  EXPECT_STREQ("bool", Value::FromBool(false).Type().c_str());

  // bad cast
  try {
    auto val = Value::FromInt(1'000'000'000L);
    EXPECT_EQ(false, val.IsBool());
    val.ToBool();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    auto val = Value::FromString("0");
    EXPECT_EQ(false, val.IsBool());
    val.ToFloat();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    auto val = ByteArray(0, 1, 2);
    EXPECT_EQ(false, val.IsBool());
    val.ToFloat();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}

TEST_F(Test, CastToInt) {
  // check type name
  EXPECT_STREQ("int", Value::FromInt(0).Type().c_str());

  // good cast
  {
    auto val = Value::FromBool(true);
    EXPECT_EQ(true, val.IsInt());
    val.ToInt();
  }

  // bad cast
  try {
    auto val = Value::FromFloat(0.1);
    EXPECT_EQ(false, val.IsInt());
    val.ToInt();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    auto val = Value::FromString("0");
    EXPECT_EQ(false, val.IsInt());
    val.ToInt();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    auto val = ByteArray(0, 1, 2);
    EXPECT_EQ(false, val.IsInt());
    val.ToInt();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}

TEST_F(Test, CastToFloat) {
  // check type name
  EXPECT_STREQ("float", Value::FromFloat(0).Type().c_str());

  // good cast
  {
    auto val = Value::FromBool(true);
    EXPECT_EQ(true, val.IsFloat());
    val.ToFloat();
  }
  {
    auto val = Value::FromInt(1'000'000'000L);
    EXPECT_EQ(true, val.IsFloat());
    val.ToFloat();
  }

  // bad cast
  try {
    auto val = Value::FromString("0");
    EXPECT_EQ(false, val.IsFloat());
    val.ToFloat();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    auto val = ByteArray<int>(0, 1, 2);
    EXPECT_EQ(false, val.IsFloat());
    val.ToFloat();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}

TEST_F(Test, CastTuple) {
  // check type name
  EXPECT_STREQ("tuple", Tuple(Int(1)).Type().c_str());

  auto val = Tuple(Str("hello"), Int(-1));

  // bad cast
  try {
    val.ToBuffer();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    val.ToDict();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    val.ToList();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    val.ToValue();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}

TEST_F(Test, CastList) {
  auto list = List(Int(0), Str("a"), Float(1));
  // check type name
  EXPECT_STREQ("list", list.Type().c_str());

  
}

TEST_F(Test, CastDict) {
  
}

TEST_F(Test, CastBuffer) {
  // create buffer
  auto numpy = Import("numpy");
  auto np_frombuffer = numpy.GetAttribute("frombuffer").ToFunc();
  auto buf = ByteArray<double>(
    {
      1, 0, 0,
      2, 1, 0 
    }
  );
  auto ndarray = np_frombuffer(buf, Str("float64"));
  
  // check type name
  EXPECT_STREQ("ndarray", ndarray.Type().c_str());

  // bad cast
  try {
    ndarray.ToDict();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    ndarray.ToList();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    ndarray.ToTuple();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    ndarray.ToValue();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}

TEST_F(Test, CastFunc) {
  
}

TEST_F(Test, CastModule) {
  // check type name
  EXPECT_STREQ("module", module_.Type().c_str());

  // bad cast
  try {
    module_.ToBuffer();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    module_.ToDict();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    module_.ToList();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    module_.ToTuple();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }

  try {
    module_.ToValue();
    FAIL();
  }
  catch (std::bad_cast &e) {
    EXPECT_STREQ("bad cast", e.what());
  }
}
