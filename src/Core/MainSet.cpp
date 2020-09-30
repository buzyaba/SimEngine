#include "Core/MainSet.h"
#include "Core/Parameters.h"
#include "Core/common.h"

#include "../lib/pugixml/include/pugixml.hpp"

#include <string.h>

void ParseString(std::string str, std::vector<double> &tt) {
  char *s = new char[str.length() + 1];
  int l = 0;
  strcpy(s, str.c_str());

  char *pp = strtok(s, " ");

  double t = 0;
  while (pp != 0) {
    sscanf(pp, "%lf", &t);
    tt.push_back(t);
    pp = strtok(NULL, " ");
    l++;
  }

  delete[] s;
}
// Тут надо подумать над парсингом строки, потому что сейчас любая ошибка (не
// соответствие имени проперти и значения) все уронит
void SetProperty(IObject *object, std::string nameProperty,
                 std::string valueProperty) {
  if (nameProperty == "Name")
    object->SetName(valueProperty);
  else {
    IProperties *tempProp = object->GetProperties()[nameProperty];
    if (tempProp) {
      std::vector<double> tempVal;
      ParseString(valueProperty, tempVal);
      std::map<std::string, double> &tmpPropMap = tempProp->GetValues();
      size_t iter = 0;
      for (auto &elem : tmpPropMap) {
        if (iter != tempVal.size()) {
          elem.second = tempVal[iter++];
        }
      }
      object->SetProperty(*tempProp);
    }
  }
}

TMainSet::TMainSet(std::string xmlMainSetConfigurationFile) {
  std::vector<TObjectOfObservation *> ObjectOfObservations;
  std::vector<TStaticObject *> StaticObjects;
  std::vector<TSmartThing *> SmartThings;

  pugi::xml_document doc;
  pugi::xml_parse_result result =
      doc.load_file(xmlMainSetConfigurationFile.c_str());
  if (result.status != pugi::status_ok)
    return;
  pugi::xml_node config = doc.child("config");
  std::vector<unsigned long int> startTime;
  std::vector<unsigned long int> endTime;

  for (pugi::xml_node iter = config.first_child(); iter != 0;
       iter = iter.next_sibling()) {
    std::string obj_type = iter.name();
    if (obj_type == "StaticObject") {
      for (pugi::xml_node static_objects_iter = iter.first_child();
           static_objects_iter != 0;
           static_objects_iter = static_objects_iter.next_sibling()) {
        std::string name = static_objects_iter.name();
        auto result =
            std::find_if(StaticObjects.begin(), StaticObjects.end(),
                         [&](auto &t) { return t->ClassName() == name; });

        if (result == std::end(StaticObjects)) {
          StaticObjects.push_back(Dll_Manager::LoadDLLObject<STATIC_OBJECT>(
              Dll_Manager::findDLLPath(getPath("/assets/models/" + name))));
          result = std::prev(StaticObjects.end());
        }

        /// Создаем новые статические объекты
        TStaticObject *newStaticObject = (*result)->Clone();
        for (pugi::xml_node iter_obj_property =
                 static_objects_iter.first_child();
             iter_obj_property != 0;
             iter_obj_property = iter_obj_property.next_sibling()) {
          std::string nameProperty = iter_obj_property.name();
          std::string valueProperty = iter_obj_property.child_value();
          SetProperty(newStaticObject, nameProperty, valueProperty);
        }
        staticObjects.push_back(newStaticObject);
        // ATTENTION
        allGObjects[newStaticObject->ClassName()].push_back(newStaticObject);
      }

    } else if (obj_type == "ObjectOfObservation") {
      for (pugi::xml_node obj_of_observe_iter = iter.first_child();
           obj_of_observe_iter != 0;
           obj_of_observe_iter = obj_of_observe_iter.next_sibling()) {
        std::string name = obj_of_observe_iter.name();
        auto result = std::find_if(
            ObjectOfObservations.begin(), ObjectOfObservations.end(),
            [&](auto &t) { return t->ClassName() == name; });

        if (result == std::end(ObjectOfObservations)) {
          ObjectOfObservations.push_back(
              Dll_Manager::LoadDLLObject<OBJECT_OF_OBSERVATION>(
                  Dll_Manager::findDLLPath(getPath("/assets/models/" + name))));
          result = std::prev(ObjectOfObservations.end());
        }

        /// Создаем новые объекты
        TObjectOfObservation *newObject = (*result)->Clone();
        for (pugi::xml_node iter_obj_property =
                 obj_of_observe_iter.first_child();
             iter_obj_property != 0;
             iter_obj_property = iter_obj_property.next_sibling()) {
          std::string nameProperty = iter_obj_property.name();
          std::string valueProperty = iter_obj_property.child_value();
          SetProperty(newObject, nameProperty, valueProperty);
        }
        objects.push_back(newObject);
        // ATTENTION
        allGObjects[newObject->ClassName()].push_back(newObject);
      }
    } else if (obj_type == "SmartThing") {
      for (pugi::xml_node smart_thing_iter = iter.first_child();
           smart_thing_iter != 0;
           smart_thing_iter = smart_thing_iter.next_sibling()) {
        std::string name = smart_thing_iter.name();
        auto result =
            std::find_if(SmartThings.begin(), SmartThings.end(),
                         [&](auto &t) { return t->ClassName() == name; });

        if (result == std::end(SmartThings)) {
          SmartThings.push_back(Dll_Manager::LoadDLLObject<SMART_THING>(
              Dll_Manager::findDLLPath(getPath("/assets/models/" + name))));
          result = std::prev(SmartThings.end());
        }

        /// Создаем новые умные вещи
        TSmartThing *newThing = (*result)->Clone();
        for (pugi::xml_node iter_obj_property = smart_thing_iter.first_child();
             iter_obj_property != 0;
             iter_obj_property = iter_obj_property.next_sibling()) {
          std::string nameProperty = iter_obj_property.name();
          std::string valueProperty = iter_obj_property.child_value();
          if (nameProperty == "Object") {
            for (int j = 0; j < objects.size(); j++) {
              if (objects[j]->GetName() == valueProperty)
                newThing->AddObject(*objects[j]);
            }
          } else
            SetProperty(newThing, nameProperty, valueProperty);
        }
        things.push_back(newThing);
      }
    }
  }
}

std::vector<TObjectOfObservation *> TMainSet::GetObjects() { return objects; }

std::vector<TStaticObject *> TMainSet::GetStaticObjects() {
  return staticObjects;
}

std::vector<TSmartThing *> TMainSet::GetThings() { return things; }

TRoomSet::TRoomSet() : TMainSet() {
  // /// пока что заглушка
  // objects.resize(1, new TTerminal("Terminal"));
  // allGObjects.insert(
  //     std::make_pair("Terminal", std::vector<TObject *>(1, objects.back())));
  // // staticObjects.resize(1, new TRoom("Room"));
  // allGObjects.insert(
  //     std::make_pair("Room", std::vector<TObject *>(1, staticObjects.back())));
  // things.resize(1, new TSmartSocket("SmartSocket"));

  // for (int i = 0; i < things.size() && i < objects.size(); i++) {
  //   things[i]->AddObject(*objects[i]);
  // }
}

TStreetSet::TStreetSet() : TMainSet() {
  // staticObjects.resize(1, new TStreet("Street"));
  // allGObjects.insert(std::make_pair("Street", std::vector<TObject*>(1,
  // staticObjects.back())));
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

  //   TTrafficLight* trafficLight = new TTrafficLight("TrafficLight",
  //   objects[3]); trafficLight->AddObject(*objects[3]);
  //   trafficLight->AddObject(*objects[2]);
  //   trafficLight->AddObject(*objects[1]);

  //   thing.resize(1, trafficLight);
}
