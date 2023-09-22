// Copyright (c) [2021-2022] [Horizon Robotics][Horizon Bole].
//
// From: https://yairchu.github.io/posts/the-priv-idiom
// 

// Copyright (c) [2021-2022] [Horizon Robotics][Horizon Bole].
//
// You can use this software according to the terms and conditions of
// the Apache v2.0.
// You may obtain a copy of Apache v2.0. at:
//
//     http: //www.apache.org/licenses/LICENSE-2.0
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See Apache v2.0 for more details.

// Created by peizhe.chen on 11/13/2021

#include "class_priv.h"

namespace MyTest {
struct ClassPriv::Priv {
  static void AddPI(const double pi, ClassPriv *priv) {
    priv->PI = pi;
  }
};

ClassPriv::ClassPriv() {
  Priv::AddPI(3.1415926, this);
}

double ClassPriv::GetPI() {
  return PI;
}

}  // namespace MyTest
