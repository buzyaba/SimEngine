#pragma once

#include <vector>
#include <string>

/**
Класс свойств объектов, описывает различные параметры, характеристики и своства различных объектов
Свойство содержит вектор double значени с соответствующими имена и\или строку - значение.
Например: свойство "координаты объекта" содержит вектор значений (1, 1, 1) с именами ("x", "y", "z")
*/
class IProperties
{
public:
  /// Возвращает вектор значени свойства
  virtual std::vector<double>& GetValues() = 0;
  /// Задает вектор значений для свойства
  virtual void SetValues(const std::vector<double>& _values) = 0;

  /// Возвращает имена для конкретных значений свойства
  virtual std::vector<std::string>& GetNames() = 0;
  /// Задает имена для значений свойства
  virtual void SetNames(const std::vector<std::string>& _names) = 0;

  /// Вохвращает значение с именем name
  virtual double GetValue(std::string name) = 0;

  /// Возвращает имя свойства
  virtual std::string GetName() = 0;

  /// Наблюдается ли это свойство стандартным сенсором
  virtual bool IsObserved() = 0;
  /// Задает наблюдается ли это свойство стандартным сенсором
  virtual void SetIsObserved(bool _isObserved) = 0;

  /// Возвращает строковое значение своства
  virtual std::string GetStringValue() = 0;
  /// Задает строковое значение свойства, после чего своство становится строковым
  virtual void SetStringValue(std::string val) = 0;
};


///Класс с базовой реализациейинтерфейса свойств объектов, описывает параметры различных объектов
class TProperties : public IProperties
{
protected:
  /// вектор значений в соответствии с именами
  std::vector<double> values;
  /// вектор имен значений
  std::vector<std::string> names;
  /// Нублюдается ли это свойство сенсорами
  bool isObserved;
  /// имя данного свойства
  std::string name;
  /// Является свойство строковым или нет
  bool isString;
  /// Строка значения сойства
  std::string stringValue;
public:

  TProperties(std::vector<double> _values, std::vector<std::string> _names,
    bool _isObserved = false, std::string _name = "");
  TProperties(int _size = 0, std::string _name = "");
  TProperties(const TProperties& properties);

  /// Возвращает вектор значени свойства
  virtual std::vector<double>& GetValues();
  /// Задает вектор значений для свойства
  virtual void SetValues(const std::vector<double>& _values);

  /// Возвращает имена для конкретных значений свойства
  virtual std::vector<std::string>& GetNames();
  /// Задает имена для значений свойства
  virtual void SetNames(const std::vector<std::string>& _names);

  /// Вохвращает значение с именем name
  virtual double GetValue(std::string name);

  /// Возвращает имя свойства
  virtual std::string GetName();

  /// Наблюдается ли это свойство стандартным сенсором
  virtual bool IsObserved();
  /// Задает наблюдается ли это свойство стандартным сенсором
  virtual void SetIsObserved(bool _isObserved);

  /// Возвращает строковое значение своства
  virtual std::string GetStringValue();
  /// Задает строковое значение свойства, после чего своство становится строковым
  virtual void SetStringValue(std::string val);
};