#include "Core/MainSet.h"


#include "SmartHouseData/Room.h"


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
  scene.resize(1, new TRoom("Room"));
  thing.resize(1, new TSmartSocket("SmartSocket"));

  for (int i = 0; i < thing.size() && i < objects.size(); i++)
  {
    thing[i]->AddObject(*objects[i]);
  }
}

TStreetSet::TStreetSet() : TMainSet()
{

}