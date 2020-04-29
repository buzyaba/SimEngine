#include <gtest/gtest.h>
#include "Core/main.h"
#include "Engine/WindowManager.hpp"
	
int main(int argc, char ** argv) {
    WindowManager window(1, 1, "Test", false);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
