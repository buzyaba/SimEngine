﻿#include "SimEngine/ObjectOfObservation.h"

TObjectOfObservation::TObjectOfObservation(std::string _name, 
  std::vector<TObjectOfObservation*> _neighboringObject,
  TObjectOfObservation* _parentObject, TObjectOfObservation* _childObject) : TObject(_name)
{
  if (_neighboringObject.size() == 1)
  {
    if (_neighboringObject[0] != nullptr)
      neighboringObject = _neighboringObject;
  }
  else
    neighboringObject = _neighboringObject;

  parentObject = _parentObject;
  
  if (_childObject != nullptr)
  {
    childObjects.push_back(_childObject);
  }
}

TObjectOfObservation::TObjectOfObservation(const TObjectOfObservation& obj) : TObject(obj)
{
  this->neighboringObject = obj.neighboringObject;
  this->childObjects = obj.childObjects;
  this->parentObject = obj.parentObject;
}

void TObjectOfObservation::AddParentObject(TObjectOfObservation* object)
{
  parentObject = object;
}

int TObjectOfObservation::AddChildObject(TObjectOfObservation* object)
{
  if (childObjects.size() == 0)
    childObjects.push_back(object);
  else
  {
    if (childObjects[0] == nullptr)
      childObjects[0] = object;
    else
    {
      childObjects.push_back(object);
    }
  }
  return childObjects.size();  
}

std::vector<TObjectOfObservation*> TObjectOfObservation::GetChildObject()
{
  return childObjects;
}

void TObjectOfObservation::AddNeighboringObject(TObjectOfObservation* object)
{
  neighboringObject.push_back(object);
}

void TObjectOfObservation::ExcludeChildObject(TObjectOfObservation* object)
{
  if (childObjects.size() == 1)
  {
    if (childObjects[0]->GetName() == object->GetName())
      childObjects[0] = nullptr;
  }
  else
  {
    for (int i = 0; i < childObjects.size(); i++)
    {
      if (childObjects[i]->GetName() == object->GetName())
      {
        std::vector<TObjectOfObservation*> newChildObjects(childObjects.size() - 1);
        for (int j = 0, t = 0; j < childObjects.size(); j++)
        {
          if (j != i)
          {
            newChildObjects[t] = childObjects[j];
            t++;
          }
        }
        childObjects = newChildObjects;
        break;
      }
    }
  }
}

void TObjectOfObservation::Update()
{
  if (childObjects.size() > 1)
    throw - 1;
}

std::vector<IProperties*>& TObjectOfObservation::GetAllProperties()
{
//   if (childObjects.size() > 0)
//   {
//     if (childObjects[0] != nullptr)
//     {
//       std::vector<IProperties*> cp = childObjects[0]->GetProperties();
//       int sizeAllProp = properties.size() + cp.size();
//       if (allProperties.size() != sizeAllProp)
//         allProperties.resize(sizeAllProp, nullptr);
//       int j = 0;
//       for (const auto& elem : properties)
//       {
//         if (elem.second != nullptr)
//         {
//           allProperties[j] = elem.second;
//           j++;
//         }
//       }
//       for (int i = 0; i < cp.size(); i++)
//       {
//         if (cp[i] != nullptr)
//         {
//           allProperties[j] = cp[i];
//           j++;
//         }
//       }
//     }
//   }
//   else
//   {
//     if (allProperties.size() != properties.size())
//       allProperties = properties;
//   }
  return allProperties;
}

// TObjectOfObservation* TObjectOfObservation::Clone()
// {
//   return new TObjectOfObservation(*this);
// }
