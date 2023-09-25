// Copyright (c) [2021-2022]
// 
// From: https://yairchu.github.io/posts/the-priv-idiom
// 

#include <vector>
#include <algorithm>
#include <sstream>

#include "version/version.h"

namespace MyTest {
std::vector<uint8_t> Version() {
  return {DCC_VERSION_MAJOR, DCC_VERSION_MINOR, DCC_VERSION_PATCH};
}

std::string VersionString() {
  const auto version = Version();
  std::ostringstream oss;
  oss << "V";
  for (size_t i = 0; i < version.size(); i++) {
    oss << (i != 0 ? "." : "") << +version[i];
  }
  return oss.str();
}
}  // namespace MyTest
