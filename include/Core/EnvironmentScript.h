#pragma once

#include <string>
#include <vector>


#include "Core/Object.h"
#include "Core/Properties.h"


/**
����� �������� ������� ������������ ������ �������
��� ��������, ����� ������, ����� �����, ��������
*/
class TPropertyInterval
{
public:
  std::string nameProperty;
  bool isSet;

  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;
  std::vector <std::vector<double>> value;

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

  std::vector<double>& GetValue(unsigned long int time)
  {
    for (int i = 0; i < startTime.size(); i++)
    {
      if ((time >= startTime[i]) && (time < endTime[i]))
        return value[i];
    }
    throw - 1;
  }

};

/// ������� ����� ����������� ������� ������������� �� ������� �������� �������
class TEnvironmentScript
{
protected:
  /// ����������� �������
  std::vector<IObject*> objects;
  /// ���(������ ����) �������
  std::string script;
  
  /// ��������� ���������� ����� � ��������������� �������� ��� ������� ��������
  std::vector<std::vector<TPropertyInterval>> objectPropertyIntervals;


  /// ������ �������� ���������� ������� � ������������ �� ��������
  std::vector <IProperties*>& ChangeProperties(int objectIndex, std::vector <IProperties*>& properties, unsigned long int time);


public:
  TEnvironmentScript(std::vector<IObject*> _objects, std::string _script);

  virtual std::vector <IProperties*>& GetObjectProperties(std::string name, unsigned long int time);
  virtual std::vector <IProperties*>& GetObjectProperties(IObject& object, unsigned long int time);

  virtual void UpdateObjectsProperties(unsigned long int time);
};