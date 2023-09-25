// Copyright (c) [2023-2024] 
//

#include "./doctest.h"
#include "./nanobench.h"
#include "class_priv.h"

TEST_CASE("TestClassPrivGetPI") {
  printf("=== CASE: TestClassPrivGetPI ===\n");
  MyTest::ClassPriv priv;
  auto pi = priv.GetPI();
  CHECK_EQ(pi, 3.1415926);
}
