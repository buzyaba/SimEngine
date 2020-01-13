#include "Core/MainSet.h"

#include "SmartHouseData/Room.h"
#include "TrafficSimData/Street.h"

#include "../lib/pugixml/include/pugixml.hpp"


TMainSet::TMainSet(std::string xmlFile)
{
  std::vector<TObjectOfObservation*> LocalObjects;
  std::vector<TScene*> LocalScene;
  std::vector<TSmartThing*> LocalThing;

  LocalScene.push_back(new TRoom("Room"));

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
    for (int i = 0; i < LocalScene.size(); i++)
    {
      if (LocalScene[i]->ClassName() == name)
      {
        TScene* newScene = LocalScene[i]->Clone();
        for (pugi::xml_node iter2 = iter.first_child(); iter2 != 0; iter2 = iter2.next_sibling())
        {
          std::string nameProperty = iter2.name();
          std::string valueProperty = iter2.child_value();
          if (nameProperty == "Name")
            newScene->SetName(valueProperty);
        }

        scene.push_back(newScene);
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
          if (nameProperty == "Name")
            newObject->SetName(valueProperty);
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
          if (nameProperty == "Name")
            newThing->SetName(valueProperty);
          if (nameProperty == "Object")
          {
            for (int j = 0; j < objects.size(); j++)
            {
              if (objects[j]->GetName() == valueProperty)
                newThing->AddObject(*objects[j]);
            }
          }
        }

        thing.push_back(newThing);
      }
    }
  }
}

std::vector<TObjectOfObservation*> TMainSet::GetObject()
{
  return objects;
}

std::vector<TScene*> TMainSet::GetScene()
{
  return scene;
}

std::vector<TSmartThing*> TMainSet::GetThing()
{
  return thing;
}

TRoomSet::TRoomSet() : TMainSet()
{
  /// пока что заглушка
  objects.resize(1, new TTerminal("Terminal"));
  scene.resize(1, new TRoom("Room"));
  thing.resize(1, new TSmartSocket("SmartSocket"));

  for (int i = 0; i < thing.size() && i < objects.size(); i++)
  {
    thing[i]->AddObject(*objects[i]);
  }
}

TStreetSet::TStreetSet() : TMainSet()
{
  /// пока что заглушка
  objects.resize(5, nullptr);
  std::vector<double> coord(2, 100);
  TCarCreator* carCreator = new TCarCreator("CarCreator");
  carCreator->SetProperty(coord, "Coordinate");

  coord[1] = 108;
  TCarDestroyer* carDestroyer = new TCarDestroyer("CarDestroyer");
  carDestroyer->SetProperty(coord, "Coordinate");

  objects[0] = carCreator;
  objects[4] = carDestroyer;

  coord[1] = 102;
  objects[1] = new TRoad("Road1");
  objects[1]->SetProperty(coord, "Coordinate");
  coord[1] = 104;
  objects[2] = new TRoad("Road2");
  objects[2]->SetProperty(coord, "Coordinate");
  coord[1] = 106;
  objects[3] = new TRoad("Road3");
  objects[3]->SetProperty(coord, "Coordinate");

  objects[3]->AddNeighboringObject(*objects[4]);
  objects[2]->AddNeighboringObject(*objects[3]);
  objects[1]->AddNeighboringObject(*objects[2]);
  objects[0]->AddNeighboringObject(*objects[1]);

  scene.resize(1, new TStreet("Street"));

  TTrafficLight* trafficLight = new TTrafficLight("TrafficLight", objects[3]);
  trafficLight->AddObject(*objects[3]);
  trafficLight->AddObject(*objects[2]);
  trafficLight->AddObject(*objects[1]);

  thing.resize(1, trafficLight);
}