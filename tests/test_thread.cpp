#include "test_root.h"

TEST_F(Test, Thread) {
  GILContext context;

  context.Lock();
  auto args = Tuple(Int(1), Str("hello"), Float(12.5));
  auto module = Import("script");
  auto func0 = module.GetAttribute("echo").ToFunc();
  auto func1 = module.GetAttribute("heavy_task").ToFunc();
  context.Unlock();

  auto sum = 0;
  std::thread th([&context, &func0, &args, &sum]() {
    for (int i = 0; i < 100000; ++i) {
      context.Lock();
      auto ret = func0.Invoke(args).ToTuple();
      sum += ret.Get(0).ToValue().ToInt();
      context.Unlock();
    }
  });

  for (int i = 0; i < 10; ++i) {
    context.Scope([&func1, &args, &sum]() {
      for (int j = 0; j < 2; ++j) {
        auto ret = func1.Invoke(args).ToTuple();
        sum += ret.Get(0).ToValue().ToInt();
      }
    });
  }
  th.join();

  EXPECT_EQ(100020, sum);
}

TEST_F(Test, ThreadAbnormal) {
  GILContext context;

  context.Release();

  try {
    context.Lock();
    FAIL();
  }
  catch (std::runtime_error& e) {
    EXPECT_STREQ("attempt to use the released object", e.what());
  }

  try {
    context.Unlock();
    FAIL();
  }
  catch (std::runtime_error& e) {
    EXPECT_STREQ("attempt to use the released object", e.what());
  }

  try {
    context.Scope([](){});
    FAIL();
  }
  catch (std::runtime_error& e) {
    EXPECT_STREQ("attempt to use the released object", e.what());
  }
}

TEST_F(ThreadingTest, ThreadClassMember) {
  context_.Lock();
  auto args = Tuple(Int(1), Str("hello"), Float(12.5));
  auto module = Import("script");
  auto func0 = module.GetAttribute("echo").ToFunc();
  auto func1 = module.GetAttribute("heavy_task").ToFunc();
  context_.Unlock();

  auto sum = 0;
  std::thread th([this, &func0, &args, &sum]() {
    for (int i = 0; i < 100000; ++i) {
      context_.Lock();
      auto ret = func0.Invoke(args).ToTuple();
      sum += ret.Get(0).ToValue().ToInt();
      context_.Unlock();
    }
  });

  for (int i = 0; i < 10; ++i) {
    context_.Scope([&func1, &args, &sum]() {
      for (int j = 0; j < 2; ++j) {
        auto ret = func1.Invoke(args).ToTuple();
        sum += ret.Get(0).ToValue().ToInt();
      }
    });
  }
  th.join();

  EXPECT_EQ(100020, sum);
}
