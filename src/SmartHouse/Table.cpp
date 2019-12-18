#include <SmartHouse/Table.hpp>

MeshRenderer* Table::mesh = nullptr;
GLuint Table::mainTexture = -1;
unsigned int Table::meshBuffer = -1;

void Table::initBuffer() {
    glGenBuffers(1, &meshBuffer);
}

void Table::initMesh() {
    mesh = new MeshRenderer(MeshType::kCube);
}

Table::Table(const glm::vec3& pos, const glm::vec3& scale) {
    if (mesh == nullptr)
        this->initMesh();
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

    transform.setPosition(pos);
    transform.setScale(scale);

    countertop.setPosition(pos + glm::vec3(0.0f, 3.0f,0.0f));
    countertop.setScale(glm::vec3(3.0f,0.1f,1.5f) * scale); 
    tableLeg1.setPosition(pos + glm::vec3(-2.9f, 1.5f,-1.4f));
    tableLeg1.setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); 
    tableLeg2.setPosition(pos + glm::vec3(-2.9f, 1.5f, 1.4f));
    tableLeg2.setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); 
    tableLeg3.setPosition(pos + glm::vec3(2.9f, 1.5f,-1.4f));
    tableLeg3.setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); 
    tableLeg4.setPosition(pos + glm::vec3(2.9f, 1.5f,1.4f));
    tableLeg4.setScale(glm::vec3(0.1f,1.5f,0.1f) * scale); 

}

void Table::setScale(const glm::vec3& _size) {

    btCollisionShape* shape = new btBoxShape(btVector3(_size.x, _size.y, _size.z));
}

void Table::setPosition(const glm::vec3& pos) {
    Primitive::setPosition(pos);
    countertop.setPosition(pos + glm::vec3(0.0f, 3.0f,0.0f));
    tableLeg1.setPosition(pos + glm::vec3(-2.9f, 1.5f,-1.4f));
    tableLeg2.setPosition(pos + glm::vec3(-2.9f, 1.5f, 1.4f));
    tableLeg3.setPosition(pos + glm::vec3(2.9f, 1.5f,-1.4f));
    tableLeg4.setPosition(pos + glm::vec3(2.9f, 1.5f,1.4f));
}

void Table::initDraw(const std::vector<Table*> objects) {
    initBuffer();
    glUseProgram(shaderProgram);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*5];
    for (int i = 0; i < objects.size(); ++i) {
        modelMatrixes[i*2] = objects[i]->countertop.getModelMatrix();
        modelMatrixes[i*2 + 1] = objects[i]->tableLeg1.getModelMatrix();
        modelMatrixes[i*2 + 2] = objects[i]->tableLeg2.getModelMatrix();
        modelMatrixes[i*2 + 3] = objects[i]->tableLeg3.getModelMatrix();
        modelMatrixes[i*2 + 4] = objects[i]->tableLeg4.getModelMatrix();
    }
    GLuint vao = objects[0]->mesh->getVAO();
    glBindBuffer(GL_ARRAY_BUFFER, Table::meshBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 5, &modelMatrixes[0], GL_STATIC_DRAW);        
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

void Table::drawElements(const std::vector<Table*> objects) {
    glUseProgram(shaderProgram);
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()*5];
    for (int i = 0; i < objects.size(); ++i) {
        modelMatrixes[i*5] = objects[i]->countertop.getModelMatrix();
        modelMatrixes[i*5 + 1] = objects[i]->tableLeg1.getModelMatrix();
        modelMatrixes[i*5 + 2] = objects[i]->tableLeg2.getModelMatrix();
        modelMatrixes[i*5 + 3] = objects[i]->tableLeg3.getModelMatrix();
        modelMatrixes[i*5 + 4] = objects[i]->tableLeg4.getModelMatrix();
    }
    glBindBuffer(GL_ARRAY_BUFFER, Table::meshBuffer);
    glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 5, &modelMatrixes[0], GL_STATIC_DRAW);
    GLuint vao = objects[0]->mesh->getVAO();
    glBindTexture(GL_TEXTURE_2D, Table::mainTexture);
    glBindVertexArray(vao);
    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size() * 5);
    glBindVertexArray(0);
    delete[] modelMatrixes;
}