
#include "db/db.h"
#include "version/version.h"

// #include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(TestGroupVersion, TestBuildVersion) {
  ASSERT_TRUE(version() < 100);
}

TEST(TestGroupVersion, Subtest_1) {
  ASSERT_TRUE(1 == 1);
}

TEST(TestGroupVersion, Subtest_2) {
  ASSERT_FALSE('a' == 'b');
}

// class MockConnection : public Connection {
//     public:
//     MOCK_METHOD(
//         bool,
//         Login,
//         (std::string& username, std::string& password),
//         (override)
//     );

//     MOCK_METHOD(
//         bool,
//         Logout,
//         (),
//         (override)
//     );
// };

// TEST(TestGroupConnection, MockTest) {
//     std::string nic = "my_nic";
//     std::string pass = "my_pass";
//     MockConnection mock_connection;

//     // Prepare mocks
//     EXPECT_CALL(mock_connection, Login(testing::_, testing::_))
//         .Times(testing::AtLeast(1))
//         .WillOnce(testing::Return(true));

//     EXPECT_CALL(mock_connection, Logout())
//         .Times(testing::AtLeast(1));

//     DataBase db(&mock_connection, nic, pass);
// }

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  // ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}
