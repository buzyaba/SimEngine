#include "Core/Properties.h"

IProperties::IProperties(std::vector<double> _values, std::vector<std::string> _names, std::string _name)
{
  name = _name;
  if (_values.size() == _names.size())
  {
    values = _values;
    names = _names;
  }
  else
  {
    throw - 1;
  }
}

IProperties::IProperties(int _size, std::string _name)
{
  name = _name;
  if (_size > -1)
  {
    values.resize(_size);
    names.resize(_size);
  }
  else
    throw - 1;

}

IProperties::IProperties(const IProperties& properties)
{
  this->values = properties.values;
  this->names = properties.names;
}

std::vector<double> IProperties::GetValues()
{
  return values;
}

void IProperties::SetValues(std::vector<double> _values)
{
  if (_values.size() == names.size())
    values = _values;
  else
    throw - 1;
}

std::vector<std::string> IProperties::GetNames()
{
  return names;
}

void IProperties::SetNames(std::vector<std::string> _names)
{
  if (_names.size() == values.size())
    names = _names;
  else
    throw - 1;
}