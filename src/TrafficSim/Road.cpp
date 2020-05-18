#include <TrafficSim/Road.hpp>
#ifdef USE_OpenGL
#include <Engine/Renderer.hpp>
#endif

std::uint32_t TRoad::meshBuffer = -1;

TRoad::TRoad(std::string _name
    #ifdef USE_OpenGL
    ,const glm::vec3& _pos, const glm::vec3& _scale
    #endif
    ): TObjectOfObservation(_name) {
    properties.insert({"IsBblockieren", new TProperties(std::map<std::string, double>{{"IsBblockieren", 0}}, false, "IsBblockieren")});
    properties.insert({"Coordinate", new TProperties(std::map<std::string, double>{{"X", 0}, {"Y", 1}, {"Z", 0}}, false, "Coordinate")});
    properties.insert({"Dimensions", new TProperties{{{"Width", 20}, {"Length", 10}, {"Height", 1}}, false, "Dimensions"}});
    properties.insert({"IsBusy", new TProperties(std::map<std::string, double>{{"IsBusy", 0}}, false, "IsBusy")});
    properties.insert({"IsHaveStandingCar", new TProperties(std::map<std::string, double>{{"IsHaveStandingCar", 0}}, true, "IsHaveStangingCar")});
    #ifdef USE_OpenGL
    otherTextures.insert({"road", Renderer::getTextures()[ROAD]});

    btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(_pos.x, _pos.y, _pos.z)));

    btCollisionShape* shape = new btBoxShape(btVector3(_scale.x, _scale.y, _scale.z));

	btScalar mass = 0.0f; 
	btVector3 Inertia(0, 0, 0);
    if(mass != 0.0f)
	    shape->calculateLocalInertia(mass, Inertia);

	btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

	rigidBody = new btRigidBody(RigidBodyCI);
    rigidBody->setRestitution(1.0f);
	rigidBody->setFriction(0.0f);

    rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	Renderer::getDynamicsWorld()->addRigidBody(rigidBody);

    transforms.resize(1);

    transforms[0].setPosition(_pos);
    transforms[0].setScale(_scale);
    #endif
}

#ifdef USE_OpenGL
void TRoad::setScale(const glm::vec3& _size) {
    btCollisionShape *shape =
      new btBoxShape(btVector3(_size.x, 1, _size.y));
    
    delete rigidBody->getCollisionShape();
    rigidBody->setCollisionShape(shape);

    transforms[0].setScale(_size);
}

void TRoad::setPosition(const glm::vec3& pos) {
    TObjectOfObservation::setPosition(pos);

    transforms[0].setPosition(pos);
}

void TRoad::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    TObjectOfObservation::setRotation(yaw, pitch, roll);

    transforms[0].setRotation(yaw, pitch, roll);
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
        modelMatrixes[i] = mat[i];
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
        modelMatrixes[i] = vec[i];
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
    #endif
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
                             const glm::vec3& _scale):TRoad(_name, _pos, _scale)
{

}

TCarCreator::TCarCreator(std::string _name, const glm::vec3& _pos, const glm::vec3& _scale): TRoad(_name, _pos, _scale) {
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