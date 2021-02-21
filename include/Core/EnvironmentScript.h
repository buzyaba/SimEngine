#pragma once

#include <string>
#include <vector>
#include <map>


#include "SimEngine/Object.h"
#include "SimEngine/Properties.h"


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

  std::vector<unsigned long int> timePoint;
  std::vector <std::map<std::string, double>> value;

  void SetProperty(IProperties& prop, int intervalCount, std::vector<unsigned long int>& _timePoint)
  {
    nameProperty = prop.GetName();
    isSet = false;
    value.resize(intervalCount);
    timePoint = _timePoint;
    for (int i = 0; i < intervalCount; i++)
    {
      value[i] = prop.GetValues();
    }
  }

  std::map<std::string, double>& GetValue(unsigned long int time)
  {
    for (int i = 0; i < timePoint.size(); i++)
    {
      if (time == timePoint[i])
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
  std::string xmlEnvironmentScriptName;
  
  /// Интервалы содержащие время и соответствующее значение для свойств объектов
  std::vector<std::map<std::string, TPropertyInterval>> objectPropertyIntervals;


  /// Меняем свойство найденного объекта в соответствии со скриптом
  std::map<std::string, IProperties*>& ChangeProperties(int objectIndex, 
        std::map<std::string, IProperties*>& properties, unsigned long int time);
  
  /// Случайное заполнение расписания
  void LoadXML(unsigned long int& maxTime);

  void ParseString(std::string str, std::vector<double>& tt);

public:
  TEnvironmentScript(std::vector<IObject*> _objects, std::string xmlEnvironmentScriptName, 
    unsigned long int& maxTime);

  virtual std::map<std::string, IProperties*>& GetObjectProperties(std::string name, unsigned long int time);
  virtual std::map<std::string, IProperties*>& GetObjectProperties(IObject& object, unsigned long int time);

  virtual void UpdateObjectsProperties(unsigned long int time);
};