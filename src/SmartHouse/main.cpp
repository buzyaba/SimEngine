#include <chrono>
#include <thread>
#include <iostream>
#include <Engine/FirstPersonView.hpp>
#include "Core/WorkManager.h"

TWorkManager* workManager;
WindowManager* WM;

int tick = 0;
bool windowFlag = false;

void initApplication();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);


int main(int argc, char** argv) {
	WM = new FirstPersonView(800, 600, "Smart House");
	auto mainSet = TSetFactory::Create(0);//!!!!
  	workManager = new TWorkManager(WM, mainSet);
  	workManager->InitDraw();
  	workManager->Start(1);
//   auto previousTime = std::chrono::high_resolution_clock::now();
//   while(!window.isWindowShouldClose()) {
//     auto currentTime = std::chrono::high_resolution_clock::now();
// 	float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
// 	Renderer::getDynamicsWorld()->stepSimulation(dt);
	delete workManager;
  	return 0;
}

void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
		
}

void initApplication() {
	Renderer::getDynamicsWorld()->setInternalTickCallback(myTickCallback);
}