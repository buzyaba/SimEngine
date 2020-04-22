#include "Core/MainSet.h"

#include "SmartHouse/Terminal.h"
#include <Engine/FirstPersonView.hpp>
#include "SmartHouse/Room.h"
#include "SmartHouse/SmartSocket.h"
// #include "TrafficSimData/Street.h"

#include "../lib/pugixml/include/pugixml.hpp"

#include <string.h>


void ParseString(std::string str, std::vector<double>& tt)
{
  char* s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char* pp = strtok(s, " ");

  double t = 0;
  while (pp != 0)
  {
    sscanf(pp, "%lf", &t);
    tt.push_back(t);
    pp = strtok(NULL, " ");
    l++;
  }

  delete[] s;
}
  // Тут надо подумать над парсингом строки, потому что сейчас любая ошибка (не соответствие имени проперти и значения) все уронит
void SetProperty(IObject* object, std::string nameProperty, std::string valueProperty)
{
  if (nameProperty == "Name")
    object->SetName(valueProperty);
  IProperties* tempProp = object->GetProperties()[nameProperty];
  if (tempProp) {
    std::vector<double> tempVal;
    ParseString(valueProperty, tempVal);
    std::map<std::string, double> tmpPropMap = tempProp->GetValues();
    size_t iter = 0;
    for (auto& elem : tmpPropMap) {
      if (iter != tempVal.size()) {
        elem.second = tempVal[iter++];
      }
    }
    object->SetProperty(*tempProp);
  }
}

TMainSet::TMainSet(std::string xmlFile)
{
  std::vector<TObjectOfObservation*> LocalObjects;
  std::vector<TStaticObject*> StaticObjects;
  std::vector<TSmartThing*> LocalThing;

  StaticObjects.push_back(new TRoom("Room"));

  LocalObjects.push_back(new TTerminal("Terminal"));

  LocalThing.push_back(new TSmartSocket("SmartSocket"));

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(xmlFile.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;

  for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
  {
    std::string name = iter.name();
    std::string value = iter.child_value();

    /// Создаем новые сцены
    for (int i = 0; i < StaticObjects.size(); i++)
    {
      if (StaticObjects[i]->ClassName() == name)
      {
        TStaticObject* newStaticObject = StaticObjects[i]->Clone();
        for (pugi::xml_node iter2 = iter.first_child(); iter2 != 0; iter2 = iter2.next_sibling())
        {
          std::string nameProperty = iter2.name();
          std::string valueProperty = iter2.child_value();
          SetProperty(newStaticObject, nameProperty, valueProperty);
        }

        staticObjects.push_back(newStaticObject);
      }
    }

    /// Создаем новые объекты
    for (int i = 0; i < LocalObjects.size(); i++)
    {
      if (LocalObjects[i]->ClassName() == name)
      {
        TObjectOfObservation* newObject = LocalObjects[i]->Clone();
        for (pugi::xml_node iter2 = iter.first_child(); iter2 != 0; iter2 = iter2.next_sibling())
        {
          std::string nameProperty = iter2.name();
          std::string valueProperty = iter2.child_value();
          SetProperty(newObject, nameProperty, valueProperty);
        }

        objects.push_back(newObject);
      }
    }

    /// Создаем новые умные вещи
    for (int i = 0; i < LocalThing.size(); i++)
    {
      if (LocalThing[i]->ClassName() == name)
      {
        TSmartThing* newThing = LocalThing[i]->Clone();
        for (pugi::xml_node iter2 = iter.first_child(); iter2 != 0; iter2 = iter2.next_sibling())
        {
          std::string nameProperty = iter2.name();
          std::string valueProperty = iter2.child_value();
          
          SetProperty(newThing, nameProperty, valueProperty);
          
          if (nameProperty == "Object")
          {
            for (int j = 0; j < objects.size(); j++)
            {
              if (objects[j]->GetName() == valueProperty)
                newThing->AddObject(*objects[j]);
            }
          }
        }

        things.push_back(newThing);
      }
    }
  }
}

std::vector<TObjectOfObservation*> TMainSet::GetObjects()
{
  return objects;
}

std::vector<TStaticObject*> TMainSet::GetStaticObjects()
{
  return staticObjects;
}

std::vector<TSmartThing*> TMainSet::GetThings()
{
  return things;
}

TRoomSet::TRoomSet() : TMainSet()
{
    /// пока что заглушка
    objects.resize(1, new TTerminal("Terminal"));
    allGObjects.insert(std::make_pair("Terminal", std::vector<TObject*>(1, objects.back())));
    staticObjects.resize(1, new TRoom("Room"));
    allGObjects.insert(std::make_pair("Room", std::vector<TObject*>(1, staticObjects.back())));
    things.resize(1, new TSmartSocket("SmartSocket"));

    for (int i = 0; i < things.size() && i < objects.size(); i++)
    {
      things[i]->AddObject(*objects[i]);
    }
}

TStreetSet::TStreetSet() : TMainSet()
{
//   /// пока что заглушка
//   objects.resize(5, nullptr);
//   std::vector<double> coord(2, 100);
//   TCarCreator* carCreator = new TCarCreator("CarCreator");
//   carCreator->SetProperty(coord, "Coordinate");

//   coord[1] = 108;
//   TCarDestroyer* carDestroyer = new TCarDestroyer("CarDestroyer");
//   carDestroyer->SetProperty(coord, "Coordinate");

//   objects[0] = carCreator;
//   objects[4] = carDestroyer;

//   coord[1] = 102;
//   objects[1] = new TRoad("Road1");
//   objects[1]->SetProperty(coord, "Coordinate");
//   coord[1] = 104;
//   objects[2] = new TRoad("Road2");
//   objects[2]->SetProperty(coord, "Coordinate");
//   coord[1] = 106;
//   objects[3] = new TRoad("Road3");
//   objects[3]->SetProperty(coord, "Coordinate");

//   objects[3]->AddNeighboringObject(*objects[4]);
//   objects[2]->AddNeighboringObject(*objects[3]);
//   objects[1]->AddNeighboringObject(*objects[2]);
//   objects[0]->AddNeighboringObject(*objects[1]);

//   scene.resize(1, new TStreet("Street"));

//   TTrafficLight* trafficLight = new TTrafficLight("TrafficLight", objects[3]);
//   trafficLight->AddObject(*objects[3]);
//   trafficLight->AddObject(*objects[2]);
//   trafficLight->AddObject(*objects[1]);

//   thing.resize(1, trafficLight);
}
