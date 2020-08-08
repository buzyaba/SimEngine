#include "BasicExamples/Sensor.h"

TSensor::TSensor(std::string _name) : packet(nullptr)
{
  SetName(_name);
  oldObjectCount = 0;
  propertyCount = 0;
}

TSensor::TSensor(const TSensor& sensor)
{
  this->packet = sensor.packet;
  this->name = sensor.name;
  this->objects = sensor.objects;
  this->oldObjectCount = sensor.oldObjectCount;
  this->propertyCount = sensor.propertyCount;
}

TDataPacket& TSensor::GetDataPacket()
{
  if (oldObjectCount < objects.size())
  {
    oldObjectCount = objects.size();
    vals.resize(oldObjectCount);
    propertyCount = 0;
    for (size_t i = 0; i < objects.size(); ++i)
    {
      if (objects[i] != nullptr)
      {
        objectsProperties[i] = objects[i]->GetProperties();
        // vals[i].resize(objectsProperties[i].size());
        // vals[i].clear();
        for (auto& elem : objectsProperties[i])
          if (elem.second != nullptr && elem.second->IsObserved())
            for (auto& iter : elem.second->GetValues())
              ++propertyCount;
        // for (int j = 0; j < objectsProperties[i].size(); j++)
        // {
        //   if (objectsProperties[i][j] != nullptr && objectsProperties[i][j]->IsObserved())
        //   {
        //     vals[i][j] = &(objectsProperties[i][j]->GetValues());
        //     propertyCount += vals[i][j]->size();
        //   }
        // }
      }
    }
  }

  if (packet == nullptr)
    packet = new TDataPacket(propertyCount * sizeof(double));

  packet->SetSize(propertyCount * sizeof(double));
  double* data = packet->GetDoubles();
  size_t t = 0;
  for (size_t i = 0; i < objectsProperties.size(); ++i)
  {
    for (auto& elem : objectsProperties[i])
          if (elem.second != nullptr && elem.second->IsObserved())
              for (auto& iter : elem.second->GetValues()) {
                  data[t++] = iter.second;
              }
    // for (int j = 0; j < vals[i].size(); j++)
    // {
    //   if (vals[i][j] != nullptr)
    //   {
    //     for (int k = 0; k < vals[i][j]->size(); k++)
    //     {
    //       data[t] = (*(vals[i][j]))[k];
    //       t++;
    //     }
    //   }
  }

  return *packet;
}

void TSensor::AddObject(TObjectOfObservation& object)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == &object)
      return;
  }
  objects.push_back(&object);
  objectsProperties.resize(objects.size());
}

void TSensor::ExcludeObject(TObjectOfObservation& object)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == &object)
    {
      objects[i] = nullptr;
      ///Дописать перепаковку
    }
  }
}

void TSensor::ExcludeObject(std::string objectName)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == objectName)
      {
        objects[i] = nullptr;

        ///Дописать перепаковку
      }
    }
  }
}

std::string TSensor::GetName()
{
  return name;
}

void TSensor::SetName(std::string _name)
{
  if (_name.length() > 0)
    name = _name;
  else
    throw - 1;
}
