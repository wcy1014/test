// Copyright (c) [2021-2022]
// 
// From: https://yairchu.github.io/posts/the-priv-idiom
// 

#pragma once

namespace MyTest {
/**
 * @brief Create a class with private function by struct priv
 * @code{.cpp}
 * UT
 * @endcode
 */
class ClassPriv {
 public:
  ClassPriv();
  double GetPI() const;

 private:
  struct Priv;
  double PI{0.0};
};
}  // namespace hobot_auto
