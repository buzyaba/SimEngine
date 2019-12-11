#pragma once
#include"Core/Properties.h"

/// Базовый класс реализующий объект имеющий набор свойств и имя.
class IObject
{
public:
  /// Задает значение своства с именем равным property.name берет значения из property
  virtual void SetProperty(IProperties& property) = 0;
  /// Задает значение values своству с именем propertyName
  virtual void SetProperty(const std::vector<double>& values, std::string propertyName) = 0;
  /// Возвращает все своства данного объекта
  virtual std::vector<IProperties*>& GetProperties() = 0;
  /// Возвращает своство с именем _name
  virtual IProperties& GetProperty(std::string _name = "") = 0;

  /// Возвращает имя объекта (используется для работы с объектами)
  virtual std::string GetName() = 0;
  /// Задает имя объекта
  virtual void SetName(std::string _name) = 0;

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName() = 0;
};

/// Реализация базового объекта имеющего набор свойств и имя.
class TObject : public IObject
{
protected:
  /// Набор свойств объекта
  std::vector<IProperties*> properties;
  /// Имя объекта
  std::string name;
public:
  TObject(std::string _name);
  TObject(const TObject& obj);

  /// Задает значение своства с именем равным property.name берет значения из property
  virtual void SetProperty(IProperties& property);
  /// Задает значение values своству с именем propertyName
  virtual void SetProperty(const std::vector<double>& values, std::string propertyName);
  /// Возвращает все своства данного объекта
  virtual std::vector<IProperties*>& GetProperties();
  /// Возвращает своство с именем _name
  virtual IProperties& GetProperty(std::string _name = "");

  /// Возвращает имя объекта (используется для работы с объектами)
  virtual std::string GetName();
  /// Задает имя объекта
  virtual void SetName(std::string _name);

  /// Возвращает имя класса (используется для динамического создания модели)
  virtual std::string ClassName();

};
