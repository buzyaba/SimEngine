#include "Core/Properties.h"

TProperties::TProperties(std::vector<double> _values, std::vector<std::string> _names, 
  bool _isObserved, std::string _name)
{
  name = _name;
  if (_values.size() == _names.size())
  {
    values = _values;
    names = _names;
    isObserved = _isObserved;
  }
  else
  {
    throw - 1;
  }
}

TProperties::TProperties(int _size, std::string _name)
{
  name = _name;
  if (_size > 0)
  {
    values.resize(_size);
    names.resize(_size);
  }
  else if (_size < 0)
    throw - 1;

}

TProperties::TProperties(const TProperties& properties)
{
  this->values = properties.values;
  this->names = properties.names;
  this->name = properties.name;
}

std::vector<double>& TProperties::GetValues()
{
  return values;
}

void TProperties::SetValues(std::vector<double> _values)
{
  if ((_values.size() == values.size()) || (values.size() == 0 || names.size() == 0))
  {
    for (int i = 0; i < values.size(); i++)
      values[i] = _values[i];
  }
  else
    throw - 1;
}

std::vector<std::string> TProperties::GetNames()
{
  return names;
}

void TProperties::SetNames(std::vector<std::string> _names)
{
  if ((_names.size() == values.size()) || (values.size() == 0 || names.size() == 0))
    names = _names;
  else
    throw - 1;
}

double TProperties::GetValue(std::string name)
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

std::string TProperties::GetName()
{
  return name;
}

bool TProperties::IsObserved()
{
  return isObserved;
}

void TProperties::SetIsObserved(bool _isObserved)
{
    isObserved = _isObserved;
}
