#include <TrafficSim/Road.hpp>
#include <TrafficSim/Car.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#ifdef USE_OpenGL
#include <Engine/Renderer.hpp>
#endif

std::uint32_t TRoad::meshBuffer = -1;
std::vector<TRoad*> TRoad::allRoads = {};

TRoad::TRoad(std::string _name
#ifdef USE_OpenGL
	, const glm::vec3& _pos, const glm::vec3& _scale
#endif
) : TObjectOfObservation(_name) {
	properties.insert({ "IsBblockieren", new TProperties(std::map<std::string, double>{ {"IsBblockieren", 0}}, false, "IsBblockieren") });
	properties.insert({ "Coordinate", new TProperties(std::map<std::string, double>{ {"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate") });
	properties.insert({ "Dimensions", new TProperties{{{"Width", 20}, {"Length", 10}, {"Height", 1}}, false, "Dimensions"} });
	properties.insert({ "IsBusy", new TProperties(std::map<std::string, double>{ {"IsBusy", 0}}, false, "IsBusy") });
	properties.insert({ "IsHaveStandingCar", new TProperties(std::map<std::string, double>{ {"IsHaveStandingCar", 0}}, true, "IsHaveStandingCar") });

	isCanGo = true;
	blocking = false;
	oldGoTime = currentStep;
#ifdef USE_OpenGL
	otherTextures.insert({ "road", Renderer::getTextures()[ROAD] });
	otherTextures.insert({ "car", Renderer::getTextures()[CAR] });

	btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(_pos.x, _pos.y, _pos.z)));

	btCollisionShape* shape = new btBoxShape(btVector3(_scale.x, _scale.y, _scale.z));

	btScalar mass = 0.0f;
	btVector3 Inertia(0, 0, 0);
	if (mass != 0.0f)
		shape->calculateLocalInertia(mass, Inertia);

	btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

	rigidBody = new btRigidBody(RigidBodyCI);
	rigidBody->setRestitution(1.0f);
	rigidBody->setFriction(0.0f);

	rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	Renderer::getDynamicsWorld()->addRigidBody(rigidBody);

	transforms.resize(2);

	transforms[0].setPosition(_pos);
	transforms[0].setScale(_scale);

	transforms[1].setPosition(_pos+glm::vec3{ 0, 0.1, 0 });
	transforms[1].setScale(glm::vec3{5, 5, 10});



	if (allRoads.size() == 0) {
		allRoads.push_back(this);
	}
	else {
		AddNeighboringObject(*allRoads.back());
		allRoads.push_back(this);
	}
#endif
}

#ifdef USE_OpenGL
void TRoad::setScale(const glm::vec3& _size) {
	btCollisionShape* shape =
		new btBoxShape(btVector3(_size.x, 1, _size.y));

	delete rigidBody->getCollisionShape();
	rigidBody->setCollisionShape(shape);

	transforms[0].setScale(_size);
}

void TRoad::setPosition(const glm::vec3& pos) {
	TObjectOfObservation::setPosition(pos);

	transforms[0].setPosition(pos);
	transforms[1].setPosition({ 0, 0.1, 0 });
	transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
}

void TRoad::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
	TObjectOfObservation::setRotation(yaw, pitch, roll);

	transforms[0].setRotation(yaw, pitch, roll);
	transforms[1].setPosition({ 0, 0.1, 0 });
	transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
}
#endif

void TRoad::initDraw(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
	setPosition({ this->properties["Coordinate"]->GetValues()["X"],
				  this->properties["Coordinate"]->GetValues()["Y"],
				  this->properties["Coordinate"]->GetValues()["Z"] });
	setScale({ this->properties["Dimensions"]->GetValues()["Length"],
				  this->properties["Dimensions"]->GetValues()["Height"],
				  this->properties["Dimensions"]->GetValues()["Width"] });
	initBuffer();
	glUseProgram(shaderProgramInstanced);
	glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
	for (int i = 0; i < objects.size(); ++i) {
		std::vector<glm::mat4> mat = objects[i]->getModelMatrixes();
		modelMatrixes[i] = mat[0];
	}

	glBindBuffer(GL_ARRAY_BUFFER, TRoad::meshBuffer);
	glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4), &modelMatrixes[0], GL_STATIC_DRAW);
	GLuint vao = meshes->getMesh(kCube)->getVAO();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glBindVertexArray(0);
	delete[] modelMatrixes;

#endif
}

void TRoad::drawElements(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
	glUseProgram(shaderProgramInstanced);
	glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
	for (int i = 0; i < objects.size(); ++i) {
		std::vector<glm::mat4> vec = objects[i]->getModelMatrixes();
		modelMatrixes[i] = vec[0];
	}
	glBindBuffer(GL_ARRAY_BUFFER, TRoad::meshBuffer);
	glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 3, &modelMatrixes[0], GL_STATIC_DRAW);
	GLuint vao = meshes->getMesh(kCube)->getVAO();
	glBindTexture(GL_TEXTURE_2D, otherTextures["road"]);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, TRoad::meshBuffer);
	glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
	GLint vpLoc = glGetUniformLocation(shaderProgramInstanced, "vp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
	glDrawElementsInstanced(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 3);
	glBindVertexArray(0);
	delete[] modelMatrixes;

	for (auto&& obj : objects) {
		if (obj->GetProperty("IsBusy").GetValue("IsBusy")) {
			GLuint vao = meshes->getMesh(kCube)->getVAO();
			glUseProgram(shaderProgramUnique);
			glBindVertexArray(vao);
			glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() *
				Renderer::getCamera()->getViewMatrix();
			GLint vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
			glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
			std::vector<glm::mat4> vec = obj->getModelMatrixes();
			GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");
			glBindTexture(GL_TEXTURE_2D, obj->getTexture("car"));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
				glm::value_ptr(vec[1]));
			glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
				GL_UNSIGNED_INT, 0);
		}
	}
#endif
}

void TRoad::Update()
{
	TObjectOfObservation::Update();

	Go();

	auto&& isHaveStandingCar = properties["IsHaveStandingCar"]->GetValues();

	if ((this->properties["IsBusy"]->GetValues()["IsBusy"] == 1) && !isCanGo)
		isHaveStandingCar["IsHaveStandingCar"] = 1;
	else
		isHaveStandingCar["IsHaveStandingCar"] = 0;

	this->properties["IsHaveStandingCar"]->SetValues(isHaveStandingCar);

	auto blocked = properties["IsBblockieren"]->GetValue("IsBblockieren");
	int sum = 0;
	auto&& it = allRoads.rbegin();
	if (blocked) {
		for (; (*it) != this; ++it);
		auto res = 
			std::accumulate(allRoads.rbegin(), it, 0,
				[&](auto a, auto b) {
					return a + b->GetProperty("IsHaveStandingCar").GetValue("IsHaveStandingCar");
				});
		isHaveStandingCar = properties["IsHaveStandingCar"]->GetValues();
		isHaveStandingCar["IsHaveStandingCar"] = res;
		properties["IsHaveStandingCar"]->SetValues(isHaveStandingCar);
	}
}

bool TRoad::IsCanGo()
{
	/// Если есть потомки, это могут быть только машины, то проверяем можем ли ехать
	if (this->childObjects.size() == 0)
		return true;
	if (this->childObjects[0] == nullptr)
	{
		return true;
	}
	else
	{
		int roadIndex = this->childObjects[0]->GetProperties()["WayIndex"]->GetValues()["WayIndex"];
		if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
		{
			/// Если дорога заблокирована, то ехать нельзя
			if (this->roadNeighboring[roadIndex]->GetProperties()["IsBblockieren"]->GetValues()["IsBblockieren"] == 1)
				return false;
			return this->roadNeighboring[roadIndex]->IsCanGo();
		}
		else
			throw - 1;
	}
	return false;
}

void TRoad::Go()
{
	if (oldGoTime != currentStep)
	{
		oldGoTime = currentStep;
		isCanGo = true;
		TObjectOfObservation* child = nullptr;
		if (this->childObjects.size() > 0)
			child = this->childObjects[0];

		if (child != nullptr)
		{
			auto&& maxWayIndex = child->GetProperties()["WayIndexCount"]->GetValues();
			maxWayIndex["WayIndexCount"] = static_cast<double>(this->roadNeighboring.size());
			child->GetProperties()["WayIndexCount"]->SetValues(maxWayIndex);
			child->Update();
		}

		isCanGo = IsCanGo();


		/// может ли машина уехать
		if (isCanGo)
		{
			//isBblockieren[0] = 0;
			//this->properties[TRoadIsBblockierenIndex]->SetValues(isBblockieren);
			if (child != nullptr)
			{
				int roadIndex = child->GetProperties()["WayIndex"]->GetValues()["WayIndex"];
				if (roadIndex >= 0 && roadIndex < this->roadNeighboring.size())
				{
					this->ExcludeChildObject(*child); //извлекли машину
					this->roadNeighboring[roadIndex]->Go(); // сходили соседом
					this->roadNeighboring[roadIndex]->AddChildObject(*child); // добавили машину соседу
					child->GetProperties()["Coordinate"]->SetValues(
						this->roadNeighboring[roadIndex]->GetProperties()["Coordinate"]->GetValues());
				}
				else
					throw - 1;
			}
		}

	}
}

void TRoad::AddNeighboringObject(TObjectOfObservation& obect)
{
	TObjectOfObservation::AddNeighboringObject(obect);

	TRoad* road = dynamic_cast<TRoad*>(&obect);
	if (road != NULL)
		roadNeighboring.push_back(road);
}


/// Добавить дочерний объект
int TRoad::AddChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 1;
	this->properties["IsBusy"]->SetValues(isBusy);

	return TObjectOfObservation::AddChildObject(obect);
}

/// Исключить дочерний объект
void TRoad::ExcludeChildObject(TObjectOfObservation& obect)
{
	auto&& isBusy = this->properties["IsBusy"]->GetValues();
	isBusy["IsBusy"] = 0;
	this->properties["IsBusy"]->SetValues(isBusy);

	TObjectOfObservation::ExcludeChildObject(obect);
}

void TRoad::initBuffer() {
#ifdef USE_OpenGL
	if (meshBuffer == -1)
		glGenBuffers(1, &meshBuffer);
#endif
}

#ifdef USE_OpenGL
TCarDestroyer::TCarDestroyer(std::string _name,
	const glm::vec3& _pos,
	const glm::vec3& _scale) :TRoad(_name, _pos, _scale)
{

}

TCarCreator::TCarCreator(std::string _name, const glm::vec3& _pos, const glm::vec3& _scale) : TRoad(_name, _pos, _scale) {
	properties.insert({ "IsCreat", new TProperties(std::map<std::string, double>{ {"IsCreat", 1}}, true, "IsCreat") });
}
#else
TCarDestroyer::TCarDestroyer(std::string _name) : TRoad(_name)
{

}

CarCreator::TCarCreator(std::string _name) : TRoad(_name) {
	properties.insert({ "IsCreat", new TProperties(std::map<std::string, double>{ {"IsCreat", 1}}, true, "IsCreat") });
}
#endif

void TCarCreator::Update()
{
	TRoad::Update();
	TObjectOfObservation* child = nullptr;
	std::default_random_engine generator;
	generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::poisson_distribution<int> poisson(100);
	if (this->childObjects.size() > 0)
		child = this->childObjects[0];
	if ((child == nullptr) && (properties["IsCreat"]->GetValues()["IsCreat"] == 1))
	{	
		if (poisson(generator)%100 > 85) {
			TCar* car = new TCar("Car");
			car->GetProperties()["Coordinate"]->SetValues(properties["Coordinate"]->GetValues());
			this->AddChildObject(*car);
		}
	}
}

void TCarDestroyer::Update()
{
	auto&& isBblockieren = this->properties["IsBblockieren"]->GetValues();
	isBblockieren["IsBblockieren"] = 0;
	this->properties["IsBblockieren"]->SetValues(isBblockieren);

	for (int i = 0; i < this->childObjects.size(); i++)
	{
		TObjectOfObservation* child = this->childObjects[i];
		if (child != nullptr)
		{
			this->ExcludeChildObject(*child);
			delete child;
		}
	}
}