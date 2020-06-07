#include "SmartHouse/Desktop.hpp"

unsigned int TDesktop::meshBuffer = -1;
#ifdef USE_OpenGL
GLuint TDesktop::mainTexture = -1;
#endif

TDesktop::TDesktop(std::string _name
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
    transforms.resize(6);

    transforms[0].setPosition(pos); //main Transform
    transforms[0].setScale(scale);
    transforms[1].setScale(glm::vec3(1.4f,1.0f,0.1f) * scale); //monitor 
    transforms[2].setScale(glm::vec3(0.2f,0.1f,0.2f) * scale); //stand1
    transforms[3].setScale(glm::vec3(0.1f,0.2f,0.1f) * scale); //stand2
    transforms[4].setScale(glm::vec3(1.3f,0.9f,0.01f) * scale); //screen
    transforms[5].setScale(glm::vec3(0.4f, 1.0f, 1.4f) * scale); // systemUnit
    transforms[1].setPosition(pos + glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(pos + glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(pos + glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(pos + glm::vec3(0.0f, 1.3f,0.095f));
    transforms[5].setPosition(pos + glm::vec3(-2.0f, 1.0f, 0.0f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
#endif
}

void TDesktop::initBuffer() {
#ifdef USE_OpenGL
    if (meshBuffer == -1)
        glGenBuffers(1, &meshBuffer);
#endif
}
#ifdef USE_OpenGL
void TDesktop::setScale(const glm::vec3& _size) {
    // TObject::setScale(_size);
    transforms[0].setScale(_size);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[5].setPosition(glm::vec3(-2.0f, 1.0f, 0.0f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}
void TDesktop::setPosition(const glm::vec3& pos) {
    TObject::setPosition(pos);
    transforms[0].setPosition(pos);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[5].setPosition(glm::vec3(-2.0f, 1.0f, 0.0f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}

void TDesktop::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    TObject::setRotation(yaw, pitch, roll);
    transforms[0].setRotation(yaw, pitch, roll);
    transforms[1].setPosition(glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(glm::vec3(0.0f, 1.3f,0.095f));
    transforms[5].setPosition(glm::vec3(-2.0f, 1.0f, 0.0f));
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}
#endif

// std::vector<glm::mat4> TDesktop::getModelMatrixes() {
//     return std::vector<glm::mat4>{transforms[0].getModelMatrix(), transforms[1].getModelMatrix(),
//         transforms[2].getModelMatrix(), transforms[3].getModelMatrix(), transforms[4].getModelMatrix()};
// }

void TDesktop::initDraw(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    for(auto& elem : objects ) {
        elem->setRotation(elem->GetProperty("Rotate").GetValues()["Yaw"], 
                  elem->GetProperty("Rotate").GetValues()["Pitch"],
                  elem->GetProperty("Rotate").GetValues()["Roll"]);
        elem->setPosition({ elem->GetProperty("Coordinate").GetValues()["X"], 
                  elem->GetProperty("Coordinate").GetValues()["Y"],
                  elem->GetProperty("Coordinate").GetValues()["Z"] });
        
    }
#endif
}

void TDesktop::drawElements(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    GLuint vao = meshes->getMesh(kCube)->getVAO();
  glUseProgram(shaderProgramUnique);
  glBindVertexArray(vao);
  glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() *
                 Renderer::getCamera()->getViewMatrix();
  GLint vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
  glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");    
  for (auto iter : objects) {
    glBindTexture(GL_TEXTURE_2D, TDesktop::mainTexture);
    std::vector<glm::mat4> vec = iter->getModelMatrixes();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[1]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[2]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[3]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[5]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, iter->getTexture("screen"));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[4]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
  }
  glBindVertexArray(0);
#endif
}

void TDesktop::Update() {
    TObjectOfObservation::Update();

    if (!isWork && this->properties["IsWork"]->GetValues()["IsWork"] == 1)
      this->properties["PowerConsumption"]->SetValues({{ "PowerConsumption", 100 }});

    if (this->properties["IsWork"]->GetValues()["IsWork"] != 0)
    {
      std::map<std::string, double>& tmp = this->properties["PowerConsumption"]->GetValues();
    //   tmp["PowerConsumption"] += (double(rand()) / RAND_MAX) * (tmp["PowerConsumption"] * 0.05) - tmp["PowerConsumption"] * 0.025;
      tmp["PowerConsumption"] = 0.001;
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


// #include <SmartHouse/Desktop.hpp>

// MeshRenderer* Desktop::mesh = nullptr;
// GLuint Desktop::mainTexture = -1;
// unsigned int Desktop::meshBuffer = -1;

// void Desktop::initBuffer() {
//     glGenBuffers(1, &meshBuffer);
// }

// void Desktop::initMesh() {
//     mesh = new MeshRenderer(MeshType::kCube);
// }

// Desktop::Desktop(const glm::vec3& pos, const glm::vec3& scale) {
//     if (mesh == nullptr)
//         this->initMesh();
//     if (mainTexture == -1)
//         mainTexture = Renderer::getTextures()[BLACK];
        
//     screenTexture = Renderer::getTextures()[SCREENSAVER];

//     btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

//     btCollisionShape* shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));

// 	btScalar mass = 0.0f; 
// 	btVector3 Inertia(0, 0, 0);
//     if(mass != 0.0f)
// 	    shape->calculateLocalInertia(mass, Inertia);

// 	btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

// 	rigidBody = new btRigidBody(RigidBodyCI);
//     rigidBody->setRestitution(1.0f);
// 	rigidBody->setFriction(0.0f);

//     rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

// 	Renderer::getDynamicsWorld()->addRigidBody(rigidBody);

//     transform.setPosition(pos);
//     transform.setScale(scale);

//     monitor.setScale(glm::vec3(1.4f,1.0f,0.1f) * scale); 
//     stand1.setScale(glm::vec3(0.2f,0.1f,0.2f) * scale); 
//     stand2.setScale(glm::vec3(0.1f,0.2f,0.1f) * scale);
//     screen.setScale(glm::vec3(1.3f,0.9f,0.01f) * scale);
//     systemBlock.setScale(glm::vec3(0.4f, 1.0f, 1.4f));  
    
//     monitor.setPosition(pos + glm::vec3(0.0f, 1.3f,0.0f));
//     stand1.setPosition(pos + glm::vec3(0.0f, 0.0f,0.0f));
//     stand2.setPosition(pos + glm::vec3(0.0f, 0.2f, 0.0f));
//     screen.setPosition(pos + glm::vec3(0.0f, 1.3f,0.095f));
//     systemBlock.setPosition(pos + glm::vec3(-2.0f, 1.0f, 0.0f));
// }

// void Desktop::setScale(const glm::vec3& _size) {

//     btCollisionShape* shape = new btBoxShape(btVector3(_size.x, _size.y, _size.z));
// }

// void Desktop::setPosition(const glm::vec3& pos) {
//     Primitive::setPosition(pos);
//     monitor.setPosition(pos + glm::vec3(0.0f, 4.4f,0.0f));
//     stand1.setPosition(pos + glm::vec3(0.0f, 3.1f,0.0f));
//     stand2.setPosition(pos + glm::vec3(0.0f, 3.2f, 0.0f));
//     screen.setPosition(pos + glm::vec3(0.0f, 4.4f,0.095f));
//     systemBlock.setPosition(pos + glm::vec3(-2.0f, 0.5f, 0.0f));
// }

// void Desktop::initDraw(const std::vector<Desktop*> objects) {
//     initBuffer();
//     glUseProgram(shaderProgram);
//     glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*4];
//     for (int i = 0; i < objects.size(); ++i) {
//         modelMatrixes[i*4] = objects[i]->monitor.getModelMatrix();
//         modelMatrixes[i*4 + 1] = objects[i]->stand2.getModelMatrix();
//         modelMatrixes[i*4 + 2] = objects[i]->stand1.getModelMatrix();
//         modelMatrixes[i*4 + 3] = objects[i]->systemBlock.getModelMatrix();
//     }
//     glBindBuffer(GL_ARRAY_BUFFER, Desktop::meshBuffer);
//     glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 4, &modelMatrixes[0], GL_STATIC_DRAW);   
//     GLuint vao = objects[0]->mesh->getVAO();
//     glBindVertexArray(vao);
//     glEnableVertexAttribArray(3);
//     glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
//     glEnableVertexAttribArray(4);
//     glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
//     glEnableVertexAttribArray(5);
//     glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
//     glEnableVertexAttribArray(6);
//     glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

//     glVertexAttribDivisor(3, 1);
//     glVertexAttribDivisor(4, 1);
//     glVertexAttribDivisor(5, 1);
//     glVertexAttribDivisor(6, 1);
//     glBindVertexArray(0);
//     delete[] modelMatrixes;    
// }

// void Desktop::drawElements(const std::vector<Desktop*> objects) {
//     glUseProgram(shaderProgram);
//     glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*4];
//     for (int i = 0; i < objects.size(); ++i) {
//         modelMatrixes[i*4] = objects[i]->monitor.getModelMatrix();
//         modelMatrixes[i*4 + 1] = objects[i]->stand2.getModelMatrix();
//         modelMatrixes[i*4 + 2] = objects[i]->stand1.getModelMatrix();
//         modelMatrixes[i*4 + 3] = objects[i]->systemBlock.getModelMatrix();
//     }
//     glBindBuffer(GL_ARRAY_BUFFER, Desktop::meshBuffer);
//     glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 4, &modelMatrixes[0], GL_STATIC_DRAW);   
//     GLuint vao = objects[0]->mesh->getVAO();
//     glBindTexture(GL_TEXTURE_2D, Desktop::mainTexture);
//     glBindVertexArray(vao);
//     glBindBuffer(GL_ARRAY_BUFFER, Desktop::meshBuffer);
//     glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
//     GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
//     glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
//     glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 4);
//     glBindVertexArray(0);
//     delete[] modelMatrixes;

//     glUseProgram(shaderProgramSingle);
//     // vao = objects[0]->mesh->getVAO();
//     glBindVertexArray(vao);
//     vpLoc = glGetUniformLocation(shaderProgramSingle, "vp");
//     glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
//     for (auto iter : objects) {
//         glBindTexture(GL_TEXTURE_2D, iter->screenTexture);
//         GLint modelLoc = glGetUniformLocation(shaderProgramSingle, "model");
//         glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
//             glm::value_ptr(iter->screen.getModelMatrix()));
//         glDrawElements(GL_TRIANGLES, iter->mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
//     }
//     glBindVertexArray(0);
// }