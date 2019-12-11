// #include <SmartHouse/Room.hpp>

// MeshRenderer* Room::mesh = nullptr;
// unsigned int Room::meshBuffer = -1;

// void Room::initBuffer() {
//     glGenBuffers(1, &meshBuffer);
// }

// void Room::initMesh() {
//     GLuint texture = Renderer::getTextures()[GRASS];
//     mesh = new MeshRenderer(MeshType::kCube);
//     mesh->setProgram(shaderProgram);
//     mesh->setTexture(texture);
// }

// Room::Room(const glm::vec3& pos, const glm::vec3& scale) {
//     if (mesh == nullptr)
//         this->initMesh();
//     if (meshBuffer == -1)
//         this->initBuffer();

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

//     floor.setPosition(pos + glm::vec3(0.0f, -0.1f,0.0f));
//     floor.setScale(glm::vec3(30.0f,0.1f,30.0f) * scale); 
//     ceiling.setPosition(pos + glm::vec3(0.0f, 10.0f,0.0f));
//     ceiling.setScale(glm::vec3(30.0f,0.1f,30.0f) * scale);
//     rightWall.setPosition(pos + glm::vec3(30.0f, 5.0f,0.0f));
//     rightWall.setScale(glm::vec3(0.1f,5.0f,30.0f) * scale);
//     leftWall.setPosition(pos + glm::vec3(-30.0f, 5.0f,0.0f));
//     leftWall.setScale(glm::vec3(0.1f,5.0f,30.0f) * scale);
//     frontWall.setPosition(pos + glm::vec3(0.0f, 5.0f, -30.0f));
//     frontWall.setScale(glm::vec3(30.0f,5.0f,0.1f) * scale); 
//     backWall.setPosition(pos + glm::vec3(0.0f, 5.0f, 30.0f));
//     backWall.setScale(glm::vec3(30.0f,5.0f,0.1f) * scale); 
    
// }

// void Room::setScale(const glm::vec3& _size) {

//     btCollisionShape* shape = new btBoxShape(btVector3(_size.x, _size.y, _size.z));
// }

// void Room::initDraw(const std::vector<Room*> objects) {
//     glUseProgram(shaderProgram);
//     glm::mat4* modelMatrixes = new glm::mat4[(int)(objects.size()*6)];
//     for (int i = 0; i < objects.size(); ++i) {
//         modelMatrixes[i*6] = objects[i]->floor.getModelMatrix();
//         modelMatrixes[i*6 + 1] = objects[i]->ceiling.getModelMatrix();
//         modelMatrixes[i*6 + 2] = objects[i]->leftWall.getModelMatrix();
//         modelMatrixes[i*6 + 3] = objects[i]->rightWall.getModelMatrix();
//         modelMatrixes[i*6 + 4] = objects[i]->frontWall.getModelMatrix();
//         modelMatrixes[i*6 + 5] = objects[i]->backWall.getModelMatrix();
//     }
//     GLuint vao = objects[0]->mesh->getVAO();
//     glBindBuffer(GL_ARRAY_BUFFER, Room::meshBuffer);
//     glBufferData(GL_ARRAY_BUFFER, (int)objects.size() * sizeof(glm::mat4) * 6, &modelMatrixes[0], GL_STATIC_DRAW);        
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


    
// }

// void Room::drawElements(const std::vector<Room*> objects) {
//     glUseProgram(shaderProgram);
//     GLuint vao = objects[0]->mesh->getVAO();
//     GLuint texture = objects[0]->mesh->getTexture();
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glBindVertexArray(vao);
//     glBindBuffer(GL_ARRAY_BUFFER, Room::meshBuffer);
//     glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
//     GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
//     glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
//     glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)(objects.size()*6));
//     glBindVertexArray(0);
// }