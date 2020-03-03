#include <gtest/gtest.h>
#include "Core/main.h"
	
// TEST(Addition, CanAddTwoNumbers)
// {
//     EXPECT_EQ(4, 2+2); 
// }

// TEST(MainTest, MainTest)
// {
//   EXPECT_NO_THROW(main0(0, 0));
// }


int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}