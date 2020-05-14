#include <TrafficSim/Street.hpp>
#ifdef USE_OpenGL
#include <Engine/Renderer.hpp>
#endif

TStreet::TStreet(std::string _name
    #ifdef USE_OpenGL
    ,const glm::vec3& _pos, 
    const glm::vec3& _scale
    #endif
    ): TStaticObject(_name) {
    properties.insert({"Dimensions", new TProperties{{{"Width", 500}, {"Length", 500}, {"Height", 1}}, false, "Dimensions"}});
    #ifdef USE_OpenGL
    otherTextures.insert({"ground", Renderer::getTextures()[GRASS]});

    btDefaultMotionState *MotionState = new btDefaultMotionState(btTransform(
      btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(_pos.x, _pos.y, _pos.z)));
      
    btCollisionShape *shape =
      new btBoxShape(btVector3(_scale.x, _scale.y, _scale.z));

    btScalar mass = 0.0f;
    btVector3 Inertia(0, 0, 0);
    if (mass != 0.0f)
        shape->calculateLocalInertia(mass, Inertia);

    btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape,
                                                        Inertia);

    rigidBody = new btRigidBody(RigidBodyCI);
    rigidBody->setRestitution(1.0f);
    rigidBody->setFriction(0.0f);

    rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

    Renderer::getDynamicsWorld()->addRigidBody(rigidBody);

    transforms.resize(1);

    transforms[0].setPosition(_pos);
    transforms[0].setScale({500, 1, 500});
    #endif
}

#ifdef USE_OpenGL
void TStreet::setScale(const glm::vec3& _size) {
    btCollisionShape *shape =
      new btBoxShape(btVector3(_size.x, 1, _size.y));
    
    delete rigidBody->getCollisionShape();
    rigidBody->setCollisionShape(shape);

    transforms[0].setScale(_size);
}

void TStreet::setPosition(const glm::vec3& pos) {
    TStaticObject::setPosition(pos);

    transforms[0].setPosition(pos);
}

void TStreet::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    TStaticObject::setRotation(yaw, pitch, roll);

    transforms[0].setRotation(yaw, pitch, roll);
}
#endif

void TStreet::drawElements(const std::vector<TObject*>& objects) {
    #ifdef USE_OpenGL
    auto vao = meshes->getMesh(kCube)->getVAO();

    glUseProgram(shaderProgramUnique);
    glBindVertexArray(vao);

    auto vp = Renderer::getCamera()->getProjectionMatrix()*
              Renderer::getCamera()->getViewMatrix();
    
    auto vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
    glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
    for (auto&& iter : objects) {
        std::vector<glm::mat4> vec = iter->getModelMatrixes();
        GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");

        glBindTexture(GL_TEXTURE_2D, iter->getTexture("ground"));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[0]));
        glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                       GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    #endif
}
