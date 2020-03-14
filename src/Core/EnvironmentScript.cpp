#include "Core/EnvironmentScript.h"

// std::vector <IProperties*>& TEnvironmentScript::ChangeProperties(int objectIndex, 
//   std::vector<IProperties*>& properties, unsigned long int time)
// {
//   for (int i = 0; i < objectPropertyIntervals[objectIndex].size(); i++)
//   {
//     if (objectPropertyIntervals[objectIndex][i].nameProperty == properties[i]->GetName())
//     {
//       properties[i]->SetValues(objectPropertyIntervals[objectIndex][i].GetValue(time));
//     }
//   }
//   return properties;
// }

// TEnvironmentScript::TEnvironmentScript(std::vector<IObject*> _objects, std::string _script, unsigned long int maxTime)
// {
//   this->objects = _objects;
//   this->script = _script;

//   int intervalCount = 200;
//   std::vector<unsigned long int> startTime;
//   std::vector<unsigned long int> endTime;
//   unsigned long int interval = maxTime / (intervalCount - 1);
//   startTime.resize(intervalCount);
//   endTime.resize(intervalCount);

//   startTime[0] = 0;
//   endTime[0] = startTime[0] + interval;

//   for (int i = 1; i < intervalCount; i++)
//   {
//     startTime[i] = endTime[i - 1];
//     endTime[i] = startTime[i] + interval;
//   }

//   objectPropertyIntervals.resize(objects.size());
//   for (int i = 0; i < objects.size(); i++)
//   {
//     objectPropertyIntervals[i].resize(objects[i]->GetProperties().size());
//     for (int j = 0; j < objects[i]->GetProperties().size(); j++)
//     {
//       objectPropertyIntervals[i][j].SetProperty(*(objects[i]->GetProperties()[j]), intervalCount, startTime, endTime);
//     }
//   }
//   objectPropertyIntervals[0][0].isSet = true;
//   for (int i = 0; i < intervalCount; i++)
//   {
//     objectPropertyIntervals[0][0].value[i][0] = rand() % 2;
//   }

//   //Добвать построение objectPropertyIntervals по скрипту.
// }

// std::vector <IProperties*>& TEnvironmentScript::GetObjectProperties(std::string name, unsigned long int time)
// {
//   for (int i = 0; i < objects.size(); i++)
//   {
//     if (objects[i] != nullptr)
//     {
//       if (objects[i]->GetName() == name)
//       {        
//         return  ChangeProperties(i, objects[i]->GetProperties(), time);
//       }
//     }
//   }
//   throw - 1;
// }

// std::vector <IProperties*>& TEnvironmentScript::GetObjectProperties(IObject& object, unsigned long int time)
// {
//   for (int i = 0; i < objects.size(); i++)
//   {
//     if (objects[i] != nullptr)
//     {
//       if (objects[i]->GetName() == object.GetName())
//       {
//         return  ChangeProperties(i, objects[i]->GetProperties(), time);
//       }
//     }
//   }
//   throw - 1;
// }

// void TEnvironmentScript::UpdateObjectsProperties(unsigned long int time)
// {
  
//   for (int i = 0; i < objects.size(); i++)
//   {
//     if (objects[i] != nullptr)
//     {
//       std::vector<IProperties*>& properties = objects[i]->GetProperties();

//       for (int j = 0; j < objectPropertyIntervals[i].size(); j++)
//       {
//         if (objectPropertyIntervals[i][j].isSet)
//         {
//           std::vector<double>& tmp = objectPropertyIntervals[i][j].GetValue(time);
//           properties[j]->SetValues(tmp);
//         }
//       }
//     }
//   }
// }
