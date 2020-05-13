#include <gtest/gtest.h>
<<<<<<< HEAD
#include "Core/main.h"
#include "Engine/WindowManager.hpp"
=======

>>>>>>> 912d0dfb076cfe2473b7c27e2cbd673d8a3a2834
	
int main(int argc, char ** argv) {
    WindowManager window(1, 1, "Test", false);
	Renderer::initTextures();
    Renderer::initPhysics();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
