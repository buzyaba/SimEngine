#pragma once
#include"Core/Properties.h"
class IObject
{
protected:
  std::vector<IProperties*> properties;

  std::string name;
public:

  virtual void SetProperty(IProperties& property, std::string _name = "") = 0;
  virtual std::vector<IProperties*> GetProperties() = 0;
  virtual IProperties& GetProperty(std::string _name = "") = 0;

  virtual std::string GetName() = 0;
  virtual void SetName(std::string _name) = 0;
};