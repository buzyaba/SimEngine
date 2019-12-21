#include <TrafficSim/Car.hpp>

MeshRenderer* Car::mesh = nullptr;
unsigned int Car::buffer = -1;
GLuint Car::texture = -1;

void Car::initMesh() {
    mesh = new MeshRenderer(MeshType::kCube);
}

Car::Car(const glm::vec3& pos) {
    if (mesh == nullptr)
        initMesh();
    if (texture == -1)
        texture = Renderer::getTextures()[CAR];
    btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

    btCollisionShape* shape = new btBoxShape(btVector3(3, 4, 8));

	btScalar mass = 10.0f; 
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
    transform.setScale(glm::vec3(3, 4, 8));
}

void Car::drawElements(const std::vector<Car*> objects) {
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
    for (int i = 0; i < objects.size(); ++i) 
        modelMatrixes[i] = objects[i]->transform.getModelMatrix();
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4), &modelMatrixes[0], GL_STATIC_DRAW);
    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    glUseProgram(shaderProgram);
    GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    GLuint vao = objects[0]->mesh->getVAO();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size());
    glBindVertexArray(0);
    delete[] modelMatrixes;
}

void Car::initDraw(const std::vector<Car*> objects) {
    glUseProgram(shaderProgram);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
    for (int i = 0; i < objects.size(); ++i) 
        modelMatrixes[i] = objects[i]->transform.getModelMatrix();
    GLuint vao = objects[0]->mesh->getVAO();
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4), &modelMatrixes[0], GL_STATIC_DRAW);        
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