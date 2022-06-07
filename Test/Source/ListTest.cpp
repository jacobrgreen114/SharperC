//
// Created by jacob on 6/7/2022.
//

#include <gtest/gtest.h>

#include "SharperC/List.hpp"

#include <iostream>

#define TEST_SUITE ListTest

TEST(TEST_SUITE, New) { auto list = List<int>::New(); }

TEST(TEST_SUITE, Add) {
  auto list = List<int>::New();

  for (int i = 0; i < 10; ++i) {
    list->Add(i * 4);
  }

  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(list->At(i), i * 4);
  }
}


TEST(TEST_SUITE, Enumerator) {
  auto array = List<int>::New();


  auto enumerator = array->GetEnumerator();
  while (enumerator->MoveNext()) {
    std::cout << enumerator->Current() << std::endl;
  }
}