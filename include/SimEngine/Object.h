#pragma once
#include "SimEngine/Properties.h"
#include <map>

/// Базовый класс реализующий объект имеющий набор свойств и имя.
class IObject
{
public:
  /// Задает значение своства с именем равным property.name берет значения из property
  virtual void SetProperty(IProperties& property) = 0;
  /// Добавляет новое свойство
  virtual void AddProperty(IProperties& property) = 0;
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

  virtual std::vector<std::vector<std::string>>& getTextures() = 0;
};

/// Реализация базового объекта имеющего набор свойств и имя.
class TObject: public IObject {
  protected:
    // Logic
    /// Имя объекта
    std::string name;
    /// Набор свойств объекта
    std::map<std::string, IProperties*> properties;

    std::vector<std::vector<std::string>> textures;
  public:
    explicit TObject(const std::string& _name);
    TObject(const TObject& obj);
    virtual ~TObject() {}
    /// Задает значение свойства с именем равным property.name берет значения из property
    virtual void SetProperty(IProperties& property) override;
    /// Задает значение values своству с именем propertyName
    virtual void SetProperty(const std::map<std::string, double>& values, std::string propertyName) override;
    /// Добавляет новое свойство
    virtual void AddProperty(IProperties& property) override;
    /// Возвращает все свойства данного объекта
    virtual std::map<std::string, IProperties*>& GetProperties() override;
    /// Возвращает свойство с именем _name
    virtual IProperties& GetProperty(const std::string& _name = "") override;

    /// Возвращает имя объекта (используется для работы с объектами)
    virtual std::string GetName() override;
    /// Задает имя объекта
    virtual void SetName(std::string name) override;
    /// Возвращает имя класса (используется для динамического создания модели)
    virtual std::string ClassName() override { return "TObject"; }
    // /// Создание клона объекта
    virtual TObject* Clone() override {return new TObject("Object");};

    virtual std::vector<std::vector<std::string>>& getTextures() override { return textures; }
};
