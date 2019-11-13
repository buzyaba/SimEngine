#include "Core/Properties.h"

IProperties::IProperties(std::vector<double> _values, std::vector<std::string> _names)
{
  if (_values.size() == _names.size())
  {
    values = _values;
    names = _names;
    size = values.size();
  }
  else
  {
    throw - 1;
  }
}

IProperties::IProperties(int _size)
{
  if (_size > -1)
  {
    size = _size;
    values.resize(size);
    names.resize(size);
  }
  else if (_size == -1)
    size = -1;
  else
    throw - 1;

}

IProperties::IProperties(const IProperties& properties)
{
  this->size = properties.size;
  this->values = properties.values;
  this->names = properties.names;
}

std::vector<double> IProperties::GetValues()
{
  return values;
}

void IProperties::SetValues(std::vector<double> _values)
{
  if ((_values.size() == size) || (size == -1))
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
  if ((_names.size() == size) || (size == -1))
    names = _names;
  else
    throw - 1;
}