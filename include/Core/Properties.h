#pragma once

#include <vector>
#include <string>


class IProperties
{
protected:
  std::vector<double> values;
  std::vector<std::string> names;
  int size;
public:

  IProperties(std::vector<double> _values, std::vector<std::string> _names);
  IProperties(int _size = -1);
  IProperties(const IProperties& properties);

  virtual std::vector<double> GetValues();
  virtual void SetValues(std::vector<double> _values);
  virtual std::vector<std::string> GetNames();
  virtual void SetNames(std::vector<std::string> _names);
};