#include "../lib/my_lib/my_lib.h"
#include "gtest/gtest.h"

TEST(MyLib, itWorks) {
  MyLib lib(1);
  EXPECT_EQ(lib.itWorks(), 1);
}
