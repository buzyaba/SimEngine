#define WITHOUT_NUMPY
#ifdef _DEBUG
#undef _DEBUG
#include <python.h>
#define _DEBUG
#else
#include <python.h>
#endif
#include <chrono>
#include <thread>
#include <iostream>
#include <Engine/FirstPersonView.hpp>

#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

#include "Core/common.h"
#include "matplotlibcpp.h"

TWorkManager* workManager;
WindowManager* WM;
namespace plt = matplotlibcpp;

int tick = 0;
bool windowFlag = false;

void initApplication();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);

void drawPlot() {
	float x_i = 0;
	std::vector<float> x;
	std::vector<float> y;
	while(x_i < 10) {
		x.emplace_back(x_i);
		y.emplace_back(std::sin(x_i));
		x_i += 0.01;
	}
	plt::plot(x, y);
	plt::show(false);
}

int main(int argc, char** argv) {
	drawPlot();
	WM = new FirstPersonView(800, 600, "Smart House");
	auto mainSet = TSetFactory::Create(0);//!!!!
  	workManager = new TWorkManager(WM, mainSet);

	// auto cwd = Renderer::getCWD();
    // auto c_cwd = cwd;
    // std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
    // auto i = c_cwd.find("SIMENGINE");
	// workManager = new TWorkManager(WM, -1, cwd.substr(0,i+9) + "/ConfigFiles/conf.xml", cwd.substr(0,i+9) + "/ConfigFiles/Room.xml", 1000, 0.0, -1.0, 1000);//60*60*24*30);

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