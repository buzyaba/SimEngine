#include <chrono>
#include <algorithm>
#include <vector>
#include <Engine/IsometricView.hpp>
#include <Core/WorkManager.h>

void initApplication();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);

TWorkManager* workManager;
WindowManager* window;

int main(int argc, char** argv) {
	window = new IsometricView(800, 600, "TrafficSim");
	workManager = new TWorkManager(window, 1);
	// auto cwd = Renderer::getCWD();
    // auto c_cwd = cwd;
    // std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
    // auto i = c_cwd.find("SIMENGINE");
	// workManager = new TWorkManager(window, -1, cwd.substr(0,i+9) + "/ConfigFiles/conf.xml", 
	// 	cwd.substr(0,i+9) + "/ConfigFiles/Street.xml", 1000, 0.0, -1.0, 1000);
	delete workManager;
	return 0;
}

void initApplication() {
	Renderer::getDynamicsWorld()->setInternalTickCallback(myTickCallback);
}

void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {

}