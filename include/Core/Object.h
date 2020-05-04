#pragma once
#include "Core/Properties.h"
#include <Engine/Transform.hpp>
#include <Engine/MeshRenderer.hpp>
#include <map>

/// Базовый класс реализующий объект имеющий набор свойств и имя.
class IObject
{
public:
  /// Задает значение своства с именем равным property.name берет значения из property
  virtual void SetProperty(IProperties& property) = 0;
  /// Задает значение values своству с именем propertyName
  virtual void SetProperty(const std::map<std::string, double>& values, std::string propertyName) = 0;
  /// Возвращает все своства данного объекта
  virtual std::map<std::string, IProperties*>& GetProperties() = 0;
  /// Возвращает своство с именем _name
  virtual IProperties& GetProperty(const std::string& _name = "") = 0;

  /// Возвращает имя объекта (используется для работы с объектами)
  virtual std::string GetName() = 0;
  /// Задает имя объекта
  virtual void SetName(std::string _name) = 0;

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName() = 0;
  /// Создание клона объекта
  virtual IObject* Clone() = 0;
};

/// Реализация базового объекта имеющего набор свойств и имя.
class TObject: public IObject {
  private:
    static void initShader();
    static void initMeshes();
  protected:
    // GL
    virtual unsigned int getMeshBuffer() = 0;
    virtual void initBuffer() = 0;
    static GLuint shaderProgramInstanced;
    static GLuint shaderProgramUnique;
    btRigidBody* rigidBody;
    std::vector<Transform> transforms;
    std::map<std::string, GLuint> otherTextures;
    MeshContainer* meshes;
    // Logic
    /// Имя объекта
    std::string name;
    /// Набор свойств объекта
    std::map<std::string, IProperties*> properties;
  public:
    explicit TObject(const std::string& _name);
    TObject(const TObject& obj);
    virtual ~TObject();
    // Logic
    /// Задает значение свойства с именем равным property.name берет значения из property
    virtual void SetProperty(IProperties& property) override;
    /// Задает значение values своству с именем propertyName
    virtual void SetProperty(const std::map<std::string, double>& values, std::string propertyName) override;
    /// Возвращает все свойства данного объекта
    virtual std::map<std::string, IProperties*>& GetProperties() override;
    /// Возвращает свойство с именем _name
    virtual IProperties& GetProperty(const std::string& _name = "") override;

    /// Возвращает имя объекта (используется для работы с объектами)
    virtual std::string GetName() override;
    /// Задает имя объекта
    virtual void SetName(std::string name) override;
    /// Возвращает имя класса (используется для динамического создания модели)
    virtual std::string ClassName() = 0;
    // /// Создание клона объекта
    virtual IObject* Clone() = 0;
    // GL
    virtual void setScale(const glm::vec3& _size) = 0;
    virtual void setPosition(const glm::vec3& pos);
    virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll);
    void setCollisionFlags(const CollisionType& _flag);
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale() { return transforms[0].getScale(); }
    btRigidBody* getRigidBody();
    bool isStatic();
    virtual void drawElements(const std::vector<TObject*>& objects) = 0;
    virtual void initDraw(const std::vector<TObject*>& objects) = 0;
    std::vector<glm::mat4> getModelMatrixes();
    GLuint getTexture(std::string _name) { return otherTextures[_name]; }
};
