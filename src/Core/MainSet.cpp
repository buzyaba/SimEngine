#include "Core/MainSet.h"


#include "SmartHouseData/Room.h"
#include "TrafficSimData/Street.h"
#include "SmartHouseData/TTerminal.h"

TMainSet::TMainSet()
{

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
  allGObject.insert(std::make_pair("Terminal", std::vector<Primitive*>(1, new GTerminal())));
//   scene.resize(1, new TRoom("Room"));
//   thing.resize(1, new TSmartSocket("SmartSocket"));

//   for (int i = 0; i < thing.size() && i < objects.size(); i++)
//   {
//     thing[i]->AddObject(*objects[i]);
//   }
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