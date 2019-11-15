#pragma once

#include <vector>
#include <string>


class IProperties
{
protected:
  std::vector<double> values;
  std::vector<std::string> names;
  std::string name;
public:

  IProperties(std::vector<double> _values, std::vector<std::string> _names, std::string _name = "");
  IProperties(int _size = -1, std::string _name = "");
  IProperties(const IProperties& properties);

  virtual std::vector<double> GetValues();
  virtual void SetValues(std::vector<double> _values);
  virtual std::vector<std::string> GetNames();
  virtual void SetNames(std::vector<std::string> _names);

  virtual double GetValue(std::string name)
  {
    int i = 0;
    for (; i < names.size(); i++)
    {
      if (names[i] == name)
        return values[i];
    }
    if (i == names.size())
      throw - 1;
  }

  std::string GetName()
  {
    return name;
  }
};