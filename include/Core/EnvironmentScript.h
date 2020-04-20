#pragma once

#include <string>
#include <vector>
#include <map>


#include "Core/Object.h"
#include "Core/Properties.h"


/**
Класс описание периода определенной работы объекта
имя свойства, время начала, время конца, значения
**/
class TPropertyInterval
{
public:
  std::string nameProperty;
  // Что это?
  bool isSet;

  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;
  std::vector <std::map<std::string, double>> value;

  void SetProperty(IProperties& prop, int intervalCount, std::vector<unsigned long int>& _startTime,
  std::vector<unsigned long int>& _endTime)
  {
    nameProperty = prop.GetName();
    isSet = false;
    value.resize(intervalCount);
    startTime = _startTime;
    endTime = _endTime;
    for (int i = 0; i < intervalCount; i++)
    {
      value[i] = prop.GetValues();
    }
  }

  std::map<std::string, double>& GetValue(unsigned long int time)
  {
    for (int i = 0; i < startTime.size(); i++)
    {
      if ((time >= startTime[i]) && (time < endTime[i]))
        return value[i];
    }
    throw - 1;
  }

};

/// Базовый класс обработчика скрипта возвращающего по времени свойства объекта
class TEnvironmentScript
{
protected:
  /// Управляемые объекты
  std::vector<IObject*> objects;
  /// Имя(полный путь) скрипта
  std::string script;
  
  /// Интервалы содержащие время и соответствующее значение для свойств объектов
  std::vector<std::map<std::string, TPropertyInterval>> objectPropertyIntervals;


  /// Меняем свойство найденного объекта в соответствии со скриптом
  std::map<std::string, IProperties*>& ChangeProperties(int objectIndex, 
        std::map<std::string, IProperties*>& properties, unsigned long int time);


public:
  TEnvironmentScript(std::vector<IObject*> _objects, std::string _script, unsigned long int maxTime = 1000);

  virtual std::map<std::string, IProperties*>& GetObjectProperties(std::string name, unsigned long int time);
  virtual std::map<std::string, IProperties*>& GetObjectProperties(IObject& object, unsigned long int time);

  virtual void UpdateObjectsProperties(unsigned long int time);
};