// Copyright (c) [2023-2024] 
//

#include "./doctest.h"
#include "./nanobench.h"
#include "version.h"

TEST_CASE("TestVersion") {
  printf("=== CASE: TestVersion ===\n");
  const auto version = MyTest::VersionString();
  CHECK_EQ(version, "V0.0.1");
}
