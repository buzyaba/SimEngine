#include "SmartHouse/Table.h"

unsigned int TTable::meshBuffer = -1;
#ifdef USE_OpenGL
GLuint TTable::mainTexture = -1;
#endif

TTable::TTable(std::string _name
#ifdef USE_OpenGL
  , const glm::vec3& pos, const glm::vec3& scale
#endif
) : TStaticObject(_name) {
    properties.insert({std::string("Coordinate"), new TProperties(std::map<std::string, double>{
        {"X", 0 }, {"Y", 0 }, {"Z", 0 } }, false, "Coordinate")});
    properties.insert({std::string("Rotate"), new TProperties(std::map<std::string, double>{
        {"Yaw", 0 }, {"Pitch", 0 }, {"Roll", 0 } }, false, "Rotate")});
    properties.insert({std::string("Dimensions"),
                     new TProperties(
                         std::map<std::string, double>{
                             {"Width", 1}, {"Length", 1}, {"Height", 1}},
                         false, "Dimensions")});
    //GL
#ifdef USE_OpenGL
    if (mainTexture == -1)
        mainTexture = Renderer::getTextures()[TABLE];
    
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
    transforms[1].setScale(glm::vec3(3.0f,0.1f,1.5f) * scale); // countertop
    transforms[2].setScale(glm::vec3(0.1f,1.5f,0.1f) * scale);  //tableLeg1
    transforms[3].setScale(glm::vec3(0.1f,1.5f,0.1f) * scale);  // tableLeg2
    transforms[4].setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); // tableLeg3
    transforms[5].setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); // tableLeg4 
    transforms[1].setPosition(glm::vec3(0.0f, 3.0f,0.0f)); // countertop
    transforms[2].setPosition(glm::vec3(-2.9f, 1.5f,-1.4f)); //tableLeg1
    transforms[3].setPosition(glm::vec3(-2.9f, 1.5f, 1.4f)); // tableLeg2
    transforms[4].setPosition(glm::vec3(2.9f, 1.5f,-1.4f));// tableLeg3
    transforms[5].setPosition(glm::vec3(2.9f, 1.5f,1.4f)); // tableLeg4
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
#endif
}

void TTable::initBuffer() {
#ifdef USE_OpenGL
    if (meshBuffer == -1)
        glGenBuffers(1, &meshBuffer);
#endif
}
#ifdef USE_OpenGL
void TTable::setScale(const glm::vec3& _size) {
    // TObject::setScale(_size);
    transforms[0].setScale(_size);
    transforms[1].setPosition(glm::vec3(0.0f, 3.0f,0.0f)); // countertop
    transforms[2].setPosition(glm::vec3(-2.9f, 1.5f,-1.4f)); //tableLeg1
    transforms[3].setPosition(glm::vec3(-2.9f, 1.5f, 1.4f)); // tableLeg2
    transforms[4].setPosition(glm::vec3(2.9f, 1.5f,-1.4f));// tableLeg3
    transforms[5].setPosition(glm::vec3(2.9f, 1.5f,1.4f)); // tableLeg4
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}
void TTable::setPosition(const glm::vec3& pos) {
    TObject::setPosition(pos);
    transforms[0].setPosition(pos);
    transforms[1].setPosition(glm::vec3(0.0f, 3.0f,0.0f)); // countertop
    transforms[2].setPosition(glm::vec3(-2.9f, 1.5f,-1.4f)); //tableLeg1
    transforms[3].setPosition(glm::vec3(-2.9f, 1.5f, 1.4f)); // tableLeg2
    transforms[4].setPosition(glm::vec3(2.9f, 1.5f,-1.4f));// tableLeg3
    transforms[5].setPosition(glm::vec3(2.9f, 1.5f,1.4f)); // tableLeg4
    
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}

void TTable::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    TObject::setRotation(yaw, pitch, roll);
    transforms[0].setRotation(yaw, pitch, roll);
    transforms[1].setPosition(glm::vec3(0.0f, 3.0f,0.0f)); // countertop
    transforms[2].setPosition(glm::vec3(-2.9f, 1.5f,-1.4f)); //tableLeg1
    transforms[3].setPosition(glm::vec3(-2.9f, 1.5f, 1.4f)); // tableLeg2
    transforms[4].setPosition(glm::vec3(2.9f, 1.5f,-1.4f));// tableLeg3
    transforms[5].setPosition(glm::vec3(2.9f, 1.5f,1.4f)); // tableLeg4
    
    transforms[1].setModelMatrix(transforms[0].getModelMatrix() * transforms[1].getModelMatrix());
    transforms[2].setModelMatrix(transforms[0].getModelMatrix() * transforms[2].getModelMatrix());
    transforms[3].setModelMatrix(transforms[0].getModelMatrix() * transforms[3].getModelMatrix());
    transforms[4].setModelMatrix(transforms[0].getModelMatrix() * transforms[4].getModelMatrix());
    transforms[5].setModelMatrix(transforms[0].getModelMatrix() * transforms[5].getModelMatrix());
}
#endif

// std::vector<glm::mat4> TTable::getModelMatrixes() {
//     return std::vector<glm::mat4>{transforms[0].getModelMatrix(), transforms[1].getModelMatrix(),
//         transforms[2].getModelMatrix(), transforms[3].getModelMatrix(), transforms[4].getModelMatrix()};
// }

void TTable::initDraw(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    for(auto& elem : objects ) {
        elem->setRotation(elem->GetProperty("Rotate").GetValues()["Yaw"], 
                  elem->GetProperty("Rotate").GetValues()["Pitch"],
                  elem->GetProperty("Rotate").GetValues()["Roll"]);
        elem->setPosition({ elem->GetProperty("Coordinate").GetValues()["X"], 
                  elem->GetProperty("Coordinate").GetValues()["Y"],
                  elem->GetProperty("Coordinate").GetValues()["Z"] });
        
    }
    // initBuffer();

    // glUseProgram(shaderProgramInstanced);
    // glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*5];
    // for (int i = 0; i < objects.size(); ++i) {
    //     std::vector<glm::mat4> vec = objects[i]->getModelMatrixes();
    //     for (size_t j = 1; j < 6; ++j) {
    //         modelMatrixes[i*5 + j-1] = vec[j];
    //     }
    // }
    // glBindBuffer(GL_ARRAY_BUFFER, TTable::meshBuffer);
    // glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 5, &modelMatrixes[0], GL_STATIC_DRAW);   
    // GLuint vao = meshes->getMesh(kCube)->getVAO();
    // glBindVertexArray(vao);
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    // glEnableVertexAttribArray(5);
    // glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    // glEnableVertexAttribArray(6);
    // glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    // glVertexAttribDivisor(3, 1);
    // glVertexAttribDivisor(4, 1);
    // glVertexAttribDivisor(5, 1);
    // glVertexAttribDivisor(6, 1);
    // glBindVertexArray(0);
    // delete[] modelMatrixes;    
#endif
}

void TTable::drawElements(const std::vector<TObject*>& objects) {
#ifdef USE_OpenGL
    glBindTexture(GL_TEXTURE_2D, TTable::mainTexture);
    GLuint vao = meshes->getMesh(kCube)->getVAO();
  glUseProgram(shaderProgramUnique);
  glBindVertexArray(vao);
  glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() *
                 Renderer::getCamera()->getViewMatrix();
  GLint vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
  glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");    
  for (auto iter : objects) {
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
                       glm::value_ptr(iter->getModelMatrixes()[4]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[5]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
  }
#endif
}
