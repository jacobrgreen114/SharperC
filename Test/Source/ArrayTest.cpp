//
// Created by jacob on 6/7/2022.
//

#include <gtest/gtest.h>

#include "SharperC/Array.hpp"

#include <iostream>

#define TEST_SUITE ArrayTest

TEST(TEST_SUITE, New) { auto array = Array<int>::New(10); }

TEST(TEST_SUITE, Enumerator) {
  auto array = Array<int>::New(10);

  auto enumerator = array->GetEnumerator();
  while (enumerator->MoveNext()) {
    std::cout << enumerator->Current() << std::endl;
  }
}