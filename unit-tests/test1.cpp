#include "vec.hpp"
#include <gtest/gtest.h>

TEST(Vec3Test, 1) {
  using namespace fnb;
  Vec3 a{1, 2, 3};
  Vec3 b{4, 5, 6};
  ASSERT_EQ(a + b, (Vec3{5, 7, 9}));
}
