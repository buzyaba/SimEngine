#include <Engine/Object.hpp>

GLuint Primitive::shaderProgram = -1;

void Primitive::initShader() {
    ShaderLoader shader;
    shaderProgram = shader.CreateProgram("../../../assets/shaders/texturedModel.vs", "../../../assets/shaders/texturedModel.fs");
}

Transform::Transform() {
    pos = glm::vec3(0);
    scale = glm::vec3(1);
    rotation = rotation.getIdentity();
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(const glm::vec3& _pos) {
    pos = _pos;
    translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    rotation = btQuaternion(yaw, pitch, roll);
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));;

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setScale(const glm::vec3& _scale) {
    scale = _scale;
    scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

Primitive::Primitive() {
    if (shaderProgram == -1) {
        Primitive::initShader();
    }
    // TextureLoader texture;
    // btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

	// btScalar mass = _mass; 
	// btVector3 Inertia(0, 0, 0);
    // if(mass != 0.0f)
	//     shape->calculateLocalInertia(mass, Inertia);

	// btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

	// btRigidBody* rigidBody = new btRigidBody(RigidBodyCI);
    // rigidBody->setRestitution(1.0f);
	// rigidBody->setFriction(0.0f);

    // rigidBody->setActivationState(DISABLE_DEACTIVATION);

	// dynamicsWorld->addRigidBody(rigidBody);

    // mesh = new MeshRenderer((MeshType)_mesh, camera, rigidBody);

    // GLuint textureShaderProgram = shader.CreateProgram("../../../assets/shaders/texturedModel.vs", "../../../assets/shaders/texturedModel.fs");
    // GLuint shaderTexture = texture.getTextureID("../../../assets/textures/");

    // mesh->setProgram(textureShaderProgram);
    // mesh->setTexture(shaderTexture);

    // rigidBody->setUserPointer(mesh);
}


void Primitive::setPosition(const glm::vec3& pos) {
    btTransform transform(rigidBody->getWorldTransform());

    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);

}

void Primitive::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btTransform transform(rigidBody->getWorldTransform());
    btQuaternion rotate(btRadians(yaw), btRadians(pitch), btRadians(roll));
    transform.setRotation(rotate);

    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);
}

void Primitive::drawElements(const std::vector<Primitive*> objects) {
    glm::mat4* modelMatrixes = new glm::mat4[(int)objects.size()];
    for (int i = 0; i < objects.size(); ++i) {
        modelMatrixes[i] = objects[i]->transform.getModelMatrix();
    }

    glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() * Renderer::getCamera()->getViewMatrix();
    glUseProgram(shaderProgram);
    GLint vpLoc = glGetUniformLocation(shaderProgram, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

    unsigned int buffer;
    GLuint vao = objects[0]->mesh->getVAO();
    GLuint texture = objects[0]->mesh->getTexture();
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

    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, objects[0]->mesh->getIndices().size(), GL_UNSIGNED_INT, 0, (int)objects.size());
    glBindVertexArray(0);
}