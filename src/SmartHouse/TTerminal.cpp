#include "SmartHouse/TTerminal.h"

unsigned int TTerminal::meshBuffer = -1;
GLuint TTerminal::mainTexture = -1;

TTerminal::TTerminal(std::string _name, const glm::vec3& pos, const glm::vec3& scale) : TObjectOfObservation(_name) {
    properties.insert({std::string("IsWork"), new TProperties(std::map<std::string, double>{{"IsWork", 0}}, false, "IsWork")});
    properties.insert({std::string("PowerConsumption"), new TProperties(std::map<std::string, double>{
        {"PowerConsumption", 0}}, true, "PowerConsumption")});
    properties.insert({std::string("Coordinate"), new TProperties(std::map<std::string, double>{
        {"X", 10}, {"Y", 10}}, false, "Coordinate")});
    isWork = false;
    //GL
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

    transforms[0].setPosition(pos);
    transforms[0].setScale(scale);
    transforms[1].setScale(glm::vec3(1.0f,1.0f,0.1f) * scale); //monitor 
    transforms[2].setScale(glm::vec3(0.2f,0.1f,0.2f) * scale); //stand1
    transforms[3].setScale(glm::vec3(0.1f,0.2f,0.1f) * scale); //stand2
    transforms[4].setScale(glm::vec3(0.9f,0.9f,0.01f) * scale); //screen
    transforms[1].setPosition(pos + glm::vec3(0.0f, 1.3f,0.0f));
    transforms[2].setPosition(pos + glm::vec3(0.0f, 0.0f,0.0f));
    transforms[3].setPosition(pos + glm::vec3(0.0f, 0.2f, 0.0f));
    transforms[4].setPosition(pos + glm::vec3(0.0f, 1.3f,0.091f));
}

void TTerminal::initBuffer() {
    if (meshBuffer == -1)
        glGenBuffers(1, &meshBuffer);
}

std::vector<glm::mat4> TTerminal::getModelMatrixes() {
    return std::vector<glm::mat4>({transforms[1].getModelMatrix(), transforms[2].getModelMatrix(), transforms[3].getModelMatrix(), });
}

void TTerminal::initDraw(const std::vector<TObject*>& objects) {
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
}

void TTerminal::drawElements(const std::vector<TObject*>& objects) {
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
    glBindTexture(GL_TEXTURE_2D, TTerminal::mainTexture);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, TTerminal::meshBuffer);
    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    GLint vpLoc = glGetUniformLocation(shaderProgramInstanced, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    glDrawElementsInstanced(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 3);
    glBindVertexArray(0);
    delete[] modelMatrixes;

    glUseProgram(shaderProgramUnique);
    // vao = objects[0]->mesh->getVAO();
    glBindVertexArray(vao);
    vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    for (auto iter : objects) {
        glBindTexture(GL_TEXTURE_2D, iter->getTexture("screen"));
        GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");
        std::vector<glm::mat4> vec = iter->getModelMatrixes();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
            glm::value_ptr(vec[4]));
        glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void TTerminal::Update() {
    // TObjectOfObservation::Update();

    // if (!isWork && this->properties[0]->GetValues()[0] == 1)
    //   this->properties[1]->SetValues({ 100 });

    // if (this->properties[0]->GetValues()[0] != 0)
    // {
    //   std::vector<double>& tmp = this->properties[1]->GetValues();
    //   tmp[0] += (double(rand()) / RAND_MAX) * (tmp[0] * 0.05) - tmp[0] * 0.025;
    //   if (tmp[0] <= 0)
    //     this->properties[0]->SetValues({ 0 });
    // }
    // else
    //   this->properties[1]->SetValues({ 0 });

    // if (this->properties[1]->GetValues()[0] <= 0)
    // {
    //   this->properties[0]->SetValues({ 0 });
    //   this->properties[1]->SetValues({ 0 });
    // }

    // isWork = this->properties[0]->GetValues()[0] == 1;
}