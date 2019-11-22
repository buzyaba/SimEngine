#pragma once

#include <vector>
#include <string>

///Класс свойств объектов, описывает параметры различных объектов
class IProperties
{
public:
  virtual std::vector<double>& GetValues() = 0;
  virtual void SetValues(std::vector<double> _values) = 0;

  virtual std::vector<std::string> GetNames() = 0;
  virtual void SetNames(std::vector<std::string> _names) = 0;

  virtual double GetValue(std::string name) = 0;
  virtual std::string GetName() = 0;
};


///Класс с базовой реализациейинтерфейса свойств объектов, описывает параметры различных объектов
class TProperties : public IProperties
{
protected:
  /// вектор значений в соответствии с именами
  std::vector<double> values;
  /// вектор имен значений
  std::vector<std::string> names;
  /// имя данного свойства
  std::string name;
public:

  TProperties(std::vector<double> _values, std::vector<std::string> _names, std::string _name = "");
  TProperties(int _size = 0, std::string _name = "");
  TProperties(const TProperties& properties);

  virtual std::vector<double>& GetValues();
  virtual void SetValues(std::vector<double> _values);

  virtual std::vector<std::string> GetNames();
  virtual void SetNames(std::vector<std::string> _names);

  virtual double GetValue(std::string name);
  virtual std::string GetName();
};