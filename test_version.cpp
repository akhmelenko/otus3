
#include "helloworld/lib.h"

#include <gtest/gtest.h>
// #include <gmock/gmock.h>

TEST(TestGroupVersion, Subtest_1) {
  ASSERT_TRUE(1 == 1);
}

TEST(TestGroupVersion, Subtest_2) {
  ASSERT_FALSE('a' == 'b');
}

TEST(TestGroupVersion, TestBuildVersion) {
  ASSERT_TRUE(version() < 100);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
//   ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}
