#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "Core/ProgramFactory.h"

#include "SimEngine/common.h"

TWorkManager::TWorkManager(TParameters& parameters_, IGraphicPresenter* presenter_)
        : parameters(parameters_),
          presenter(presenter_) {
    currentTime = 0;
    currentStep = 0;
    mainSet = TSetFactory::Create(parameters.xmlMainSetConfigurationFile);

    objects = mainSet->GetObjects();
    things = mainSet->GetThings();
    staticObjects = mainSet->GetStaticObjects();

    if (parameters.millisecondsInTimeStep < 0)
        parameters.millisecondsInTimeStep = 0;

    std::vector<IObject*> allObject(objects.size() + things.size());
    int j = 0;
    for (int i = 0; i < objects.size(); i++) {
        allObject[j] = objects[i];
        j++;
    }
    for (int i = 0; i < things.size(); i++) {
        allObject[j] = things[i];
        j++;
    }

    script = new TExternalActionSchedule(objects, parameters.xmlExternalActionScheduleName);
    program = TProgramFactory::Create(things);
    storage = new TDataStore(allObject, "../../A");

    startWork = std::chrono::steady_clock::now();
}

TWorkManager::~TWorkManager() {
    Dll_Manager::FreeDllManager();
}

void TWorkManager::Iteration(const std::size_t step, const std::chrono::milliseconds& iterTime) {
    time = step * parameters.millisecondsInTimeStep;
    currentTime = time;
    currentStep = step;
    auto start = std::chrono::steady_clock::now();
    script->UpdateObjectsProperties(time);

    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Update();
    }

    storage->AddAllProperties(time);
    program->Run(currentTime, currentStep);

    presenter->transformsUpdateSignal();
    
    auto end = std::chrono::steady_clock::now();
    auto delta = end - start;
    if (iterTime > delta) {
        auto sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(iterTime - delta);
        std::this_thread::sleep_for(sleepTime);
    }
}

void TWorkManager::Start() {
    std::cout << "Start\n Max Iter = " << parameters.maxStep << std::endl;
    std::cout << "Max Time = " << parameters.maxStep * parameters.millisecondsInTimeStep << " ms"
              << std::endl;
    std::cout << "time acceleration = " << parameters.timeAcceleration << " X" << std::endl;

    if (parameters.timeAcceleration <= 0 ||
        parameters.timeAcceleration > parameters.millisecondsInTimeStep)
        parameters.timeAcceleration = static_cast<double>(parameters.millisecondsInTimeStep);

    startWork = std::chrono::steady_clock::now();
    time = 0;
    std::chrono::milliseconds iterTime(
        static_cast<std::size_t>(parameters.millisecondsInTimeStep / parameters.timeAcceleration));

    for (std::size_t step = 0; step < parameters.maxStep; step++) {
        Iteration(step, iterTime);
    }

    std::chrono::time_point<std::chrono::steady_clock> endWork = std::chrono::steady_clock::now();
    std::chrono::milliseconds deltaWork =
        std::chrono::duration_cast<std::chrono::milliseconds>(endWork - startWork);
    std::cout << "End Work\n Time Work = \t" << deltaWork.count() << " ms.\n "
              << "Simulation time = \t"
              << static_cast<double>(parameters.maxStep) * parameters.millisecondsInTimeStep / 60000
              << " minutes\n"
              << std::endl;

    // storage->PrintToFile();
    // presenter->stopGraphicManager();
    program->End();
}

void TWorkManager::Stop() {
    parameters.maxStep = -1;
}

void TWorkManager::SetMillisecondsInTimeStep(unsigned int _milliseconds) {
    if (_milliseconds > 0)
        parameters.millisecondsInTimeStep = _milliseconds;
    else
        parameters.millisecondsInTimeStep = 0;
}

void sendObjectsImpl(TObjectOfObservation* elem, IGraphicPresenter* presenter) {
    for (auto& child : elem -> GetChildObjects())
        sendObjectsImpl(child, presenter);
    if (elem->isDrawable())
 	       presenter->addTObject(elem);
}

void TWorkManager::sendObjects() {
    for (auto& elem : mainSet->GetStaticObjects()) {
		if (elem->isDrawable())
 	       presenter->addTObject(elem);
    }
	for (auto& elem : mainSet->GetThings()) {
		if (elem->isDrawable())
 	       presenter->addTObject(elem);
    }
	for (auto& elem : mainSet->GetObjects()) {
		sendObjectsImpl(elem, presenter);
    }
}