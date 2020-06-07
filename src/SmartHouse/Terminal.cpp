#include "SmartHouse/Terminal.h"

unsigned int TTerminal::meshBuffer = -1;
#ifdef USE_OpenGL
GLuint TTerminal::mainTexture = -1;
#endif

TTerminal::TTerminal(std::string _name
#ifdef USE_OpenGL
  , const glm::vec3& pos, const glm::vec3& scale
#endif
) : TObjectOfObservation(_name) {
    properties.insert({std::string("IsWork"), new TProperties(std::map<std::string, double>{{"IsWork", 0}}, false, "IsWork")});
    properties.insert({std::string("PowerConsumption"), new TProperties(std::map<std::string, double>{
        {"PowerConsumption", 0}}, true, "PowerConsumption")});
    properties.insert({std::string("Coordinate"), new TProperties(std::map<std::string, double>{
        {"X", 0 }, {"Y", 0 }, {"Z", 0 } }, false, "Coordinate")});
    properties.insert({std::string("Rotate"), new TProperties(std::map<std::string, double>{
        {"Yaw", 0 }, {"Pitch", 0 }, {"Roll", 0 } }, false, "Rotate")});
    isWork = false;
    //GL
#ifdef USE_OpenGL
    if (mainTexture == -1)
        mainTexture = Renderer::getTextures()[MONITOR];
    
    otherTextures.insert({"screen", Renderer::getTextures()[SCREENSAVER]});

    btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

    btCollisionShape* shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));

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
    transforms.resize(5);

    transforms[0].setPosition(pos); //main Transform
    transforms[0].setScale(scale);
    transforms[1].setScale(glm::vec3(1.0f,1.0f,0.1f) * scale); //monitor 
    transforms[2].setScale(glm::vec3(0.2f,0.1f,0.2f) * scale); //stand1
    transforms[3].setScale(glm::vec3(0.1f,0.2f,0.1f) * scale); //stand2
    transforms[4].setScale(glm::vec3(0.9f,0.9f,0.01f) * scale); //screen
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
#endif
}

void TTerminal::initBuffer() {
#ifdef USE_OpenGL
    if (meshBuffer == -1)
        glGenBuffers(1, &meshBuffer);
#endif
}
#ifdef USE_OpenGL
void TTerminal::setScale(const glm::vec3& _size) {
    // TObject::setScale(_size);
    transforms[0].setScale(_size);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
}
void TTerminal::setPosition(const glm::vec3& pos) {
    TObject::setPosition(pos);
    transforms[0].setPosition(pos);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    // transforms[1].setPosition(pos + glm::vec3(0.0f, 1.3f,0.0f));
    // transforms[2].setPosition(pos + glm::vec3(0.0f, 0.0f,0.0f));
    // transforms[3].setPosition(pos + glm::vec3(0.0f, 0.2f, 0.0f));
    // transforms[4].setPosition(pos + glm::vec3(0.0f, 1.3f,0.095f));
}

void TTerminal::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    TObject::setRotation(yaw, pitch, roll);
    transforms[0].setRotation(yaw, pitch, roll);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
}
#endif

// std::vector<glm::mat4> TTerminal::getModelMatrixes() {
//     return std::vector<glm::mat4>{transforms[0].getModelMatrix(), transforms[1].getModelMatrix(),
//         transforms[2].getModelMatrix(), transforms[3].getModelMatrix(), transforms[4].getModelMatrix()};
// }

void TTerminal::initDraw(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    for(auto& elem : objects ) {
        elem->setRotation(elem->GetProperty("Rotate").GetValues()["Yaw"], 
                  elem->GetProperty("Rotate").GetValues()["Pitch"],
                  elem->GetProperty("Rotate").GetValues()["Roll"]);
        elem->setPosition({ elem->GetProperty("Coordinate").GetValues()["X"], 
                  elem->GetProperty("Coordinate").GetValues()["Y"],
                  elem->GetProperty("Coordinate").GetValues()["Z"] });
    }
    initBuffer();

    glUseProgram(shaderProgramInstanced);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*3];
    for (int i = 0; i < objects.size(); ++i) {
        std::vector<glm::mat4> vec = objects[i]->getModelMatrixes();
        for (size_t j = 1; j < 4; ++j) {
            modelMatrixes[i*3 + j-1] = vec[j];
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, TTerminal::meshBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 3, &modelMatrixes[0], GL_STATIC_DRAW);   
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

void TTerminal::drawElements(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    glUseProgram(shaderProgramInstanced);
    glBindTexture(GL_TEXTURE_2D, TTerminal::mainTexture);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*3];
    for (int i = 0; i < objects.size(); ++i) {
        std::vector<glm::mat4> vec = objects[i]->getModelMatrixes();
        for (size_t j = 1; j < 4; ++j) {
            modelMatrixes[i*3 + j-1] = vec[j];
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, TTerminal::meshBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 3, &modelMatrixes[0], GL_STATIC_DRAW);
    GLuint vao = meshes->getMesh(kCube)->getVAO();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, TTerminal::meshBuffer);
    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    GLint vpLoc = glGetUniformLocation(shaderProgramInstanced, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    glDrawElementsInstanced(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 3);
    glBindVertexArray(0);
    delete[] modelMatrixes;

    glUseProgram(shaderProgramUnique);
    glBindVertexArray(vao);
    vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    for (auto iter : objects) {
        glBindTexture(GL_TEXTURE_2D, iter->getTexture("screen"));
        GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
            glm::value_ptr(iter->getModelMatrixes()[4]));
        glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
#endif
}

void TTerminal::Update() {
    TObjectOfObservation::Update();

    if (!isWork && this->properties["IsWork"]->GetValues()["IsWork"] == 1)
      this->properties["PowerConsumption"]->SetValues({{ "PowerConsumption", 100 }});

    if (this->properties["IsWork"]->GetValues()["IsWork"] != 0)
    {
      std::map<std::string, double>& tmp = this->properties["PowerConsumption"]->GetValues();
    //   tmp["PowerConsumption"] += (double(rand()) / RAND_MAX) * (tmp["PowerConsumption"] * 0.05) - tmp["PowerConsumption"] * 0.025;
      tmp["PowerConsumption"] = 0.00134;
      if (tmp["PowerConsumption"] <= 0)
        this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});
    }
    else
      this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});

    if (this->properties["PowerConsumption"]->GetValues()["PowerConsumption"] <= 0)
    {
      this->properties["IsWork"]->SetValues({{"IsWork", 0}});
      this->properties["PowerConsumption"]->SetValues({{"PowerConsumption", 0 }});
    }

    isWork = this->properties["IsWork"]->GetValues()["IsWork"] == 1;
    /// ���������� ��������
#ifdef USE_OpenGL
    if (isWork) setScreenTexture(Renderer::getTextures()[WINDOWS]);
    else setScreenTexture(Renderer::getTextures()[SCREENSAVER]);
#endif
}
