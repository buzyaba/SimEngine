#include <SmartHouse/Monitor.hpp>

MeshRenderer* Monitor::mesh = nullptr;
unsigned int Monitor::meshBuffer = -1;
unsigned int Monitor::meshScreenBuffer = -1;

void Monitor::initBuffer() {
    glGenBuffers(1, &meshBuffer);
    glGenBuffers(1, &meshScreenBuffer);
}

void Monitor::initMesh() {
    GLuint texture = Renderer::getTextures()[BLACK];
    mesh = new MeshRenderer(MeshType::kCube);
    mesh->setProgram(shaderProgram);
    mesh->setTexture(texture);
}

Monitor::Monitor(const glm::vec3& pos, const glm::vec3& scale) {
    if (mesh == nullptr)
        this->initMesh();
    if (meshBuffer == -1)
        this->initBuffer();
    
    GLuint texture = Renderer::getTextures()[SCREENSAVER];
    meshScreen = new MeshRenderer(MeshType::kCube);
    meshScreen->setProgram(shaderProgram);
    meshScreen->setTexture(texture);

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

    transform.setPosition(pos);
    transform.setScale(scale);

    monitor.setPosition(pos + glm::vec3(0.0f, 4.4f,0.0f));
    monitor.setScale(glm::vec3(1.0f,1.0f,0.1f) * scale); 
    stand1.setPosition(pos + glm::vec3(0.0f, 3.1f,0.0f));
    stand1.setScale(glm::vec3(0.2f,0.1f,0.2f) * scale); 
    stand2.setPosition(pos + glm::vec3(0.0f, 3.2f, 0.0f));
    stand2.setScale(glm::vec3(0.1f,0.3f,0.1f) * scale);
    screen.setPosition(pos + glm::vec3(0.0f, 4.4f,0.091f));
    screen.setScale(glm::vec3(0.9f,0.9f,0.01f) * scale);  
}

void Monitor::setScale(const glm::vec3& _size) {

    btCollisionShape* shape = new btBoxShape(btVector3(_size.x, _size.y, _size.z));
}

void Monitor::initDraw(const std::vector<Monitor*> objects) {
    glUseProgram(shaderProgram);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*3];
    for (int i = 0; i < objects.size(); ++i) {
        modelMatrixes[i*2] = objects[i]->monitor.getModelMatrix();
        modelMatrixes[i*2 + 1] = objects[i]->stand1.getModelMatrix();
        modelMatrixes[i*2 + 2] = objects[i]->stand2.getModelMatrix();
    }
    glBindBuffer(GL_ARRAY_BUFFER, Monitor::meshBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 3, &modelMatrixes[0], GL_STATIC_DRAW);   
    GLuint vao = objects[0]->mesh->getVAO();
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

    glm::mat4* modelMatrixes1 = new glm::mat4[(int)objects.size()];
    for (int i = 0; i < objects.size(); ++i) {
        modelMatrixes1[i] = objects[i]->screen.getModelMatrix();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, Monitor::meshScreenBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4), &modelMatrixes1[0], GL_STATIC_DRAW);   
    vao = objects[0]->meshScreen->getVAO();
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
    
}

void Monitor::drawElements(const std::vector<Monitor*> objects) {
    glUseProgram(shaderProgram);
    GLuint vao = objects[0]->mesh->getVAO();
    GLuint texture = objects[0]->mesh->getTexture();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, Monitor::meshBuffer);
    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 3);
    glBindVertexArray(0);
    texture = objects[0]->meshScreen->getTexture();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, Monitor::meshScreenBuffer);
    vao = objects[0]->meshScreen->getVAO();
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size());
    glBindVertexArray(0);
}