#include <TrafficSim/Car.hpp>
#include <random>
#include <chrono>
#ifdef USE_OpenGL
#include <Engine/Renderer.hpp>
#endif

std::uint32_t TCar::meshBuffer = -1;

TCar::TCar(std::string _name
#ifdef USE_OpenGL
	, const glm::vec3& _pos, const glm::vec3& _scale
#endif
) : TObjectOfObservation(_name) {
	properties.insert({ "WayIndex", new TProperties(std::map<std::string, double>{ {"WayIndex", -1}}, true, "WayIndex") });
	properties.insert({ "Coordinate", new TProperties(std::map<std::string, double>{ {"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate") });
	properties.insert({ "Dimensions", new TProperties{{{"Width", 8}, {"Length", 15}, {"Height", 4}}, false, "Dimensions"} });
	properties.insert({ "WayIndexCount", new TProperties(std::map<std::string, double>{ {"WayIndexCount", 0}}, false, "WayIndexCount") });
#ifdef USE_OpenGL
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

	transforms.resize(1);

	transforms[0].setPosition(_pos);
	transforms[0].setScale(_scale);
#endif
}

void TCar::Update()
{
	TObjectOfObservation::Update();
	auto&& val = this->properties["WayIndex"]->GetValues();
	std::default_random_engine generator;
	generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::poisson_distribution<int> poisson;
	val["WayIndex"] = poisson(generator) % static_cast<int>(this->properties["WayIndexCount"]->GetValues()["WayIndexCount"]);
	this->properties["WayIndex"]->SetValues(val);
}

#ifdef USE_OpenGL
void TCar::setScale(const glm::vec3& _size) {
	transforms[0].setScale(_size);
}

void TCar::setPosition(const glm::vec3& pos) {
	TObjectOfObservation::setPosition(pos);

	transforms[0].setPosition(pos);
}

void TCar::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
	TObjectOfObservation::setRotation(yaw, pitch, roll);

	transforms[0].setRotation(yaw, pitch, roll);
}
#endif

void TCar::initDraw(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
	//setPosition({ this->properties["Coordinate"]->GetValues()["X"],
	//			  this->properties["Coordinate"]->GetValues()["Y"],
	//			  this->properties["Coordinate"]->GetValues()["Z"] });
	//setScale({ this->properties["Dimensions"]->GetValues()["Length"],
	//			  this->properties["Dimensions"]->GetValues()["Width"],
	//			  this->properties["Dimensions"]->GetValues()["Height"] });
	//initBuffer();
	//glUseProgram(shaderProgramInstanced);
	//glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
	//for (int i = 0; i < objects.size(); ++i) {
	//	std::vector<glm::mat4> mat = objects[i]->getModelMatrixes();
	//	modelMatrixes[i] = mat[0];
	//}

	//glBindBuffer(GL_ARRAY_BUFFER, TCar::meshBuffer);
	//glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4), &modelMatrixes[0], GL_STATIC_DRAW);
	//GLuint vao = meshes->getMesh(kCube)->getVAO();
	//glBindVertexArray(vao);
	//glEnableVertexAttribArray(3);
	//glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	//glEnableVertexAttribArray(5);
	//glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	//glEnableVertexAttribArray(6);
	//glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	//glVertexAttribDivisor(3, 1);
	//glVertexAttribDivisor(4, 1);
	//glVertexAttribDivisor(5, 1);
	//glVertexAttribDivisor(6, 1);
	//glBindVertexArray(0);
	//delete[] modelMatrixes;
#endif
}

void TCar::drawElements(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
	//glUseProgram(shaderProgramInstanced);
	//glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
	//for (int i = 0; i < objects.size(); ++i) {
	//	std::vector<glm::mat4> vec = objects[i]->getModelMatrixes();
	//	modelMatrixes[i] = vec[0];
	//}
	//glBindBuffer(GL_ARRAY_BUFFER, TCar::meshBuffer);
	//glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 3, &modelMatrixes[0], GL_STATIC_DRAW);
	//GLuint vao = meshes->getMesh(kCube)->getVAO();
	//glBindTexture(GL_TEXTURE_2D, otherTextures["car"]);
	//glBindVertexArray(vao);
	//glBindBuffer(GL_ARRAY_BUFFER, TCar::meshBuffer);
	//glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
	//GLint vpLoc = glGetUniformLocation(shaderProgramInstanced, "vp");
	//glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
	//glDrawElementsInstanced(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 3);
	//glBindVertexArray(0);
	//delete[] modelMatrixes;
#endif
}

void TCar::initBuffer() {
#ifdef USE_OpenGL
	if (meshBuffer == -1)
		glGenBuffers(1, &meshBuffer);
#endif
}