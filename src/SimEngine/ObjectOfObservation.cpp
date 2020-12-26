#include "SimEngine/ObjectOfObservation.h"
#include <algorithm>

TObjectOfObservation::TObjectOfObservation(std::string _name,
                                           std::vector<TObjectOfObservation*> _neighboringObject,
                                           TObjectOfObservation* _parentObject,
                                           TObjectOfObservation* _childObject)
        : TObject(_name) {
    if (_neighboringObject.size() == 1) {
        if (_neighboringObject[0] != nullptr)
            neighboringObject = _neighboringObject;
    }
    else
        neighboringObject = _neighboringObject;

    parentObject = _parentObject;

    if (_childObject != nullptr) {
        childObjects.push_back(_childObject);
    }
}

TObjectOfObservation::TObjectOfObservation(const TObjectOfObservation& obj) : TObject(obj) {
    this->neighboringObject = obj.neighboringObject;
    this->childObjects = obj.childObjects;
    this->parentObject = obj.parentObject;
}

void TObjectOfObservation::AddParentObject(TObjectOfObservation& obect) {
    parentObject = &obect;
}

int TObjectOfObservation::AddChildObject(TObjectOfObservation& obect) {
    if (childObjects.size() == 0)
        childObjects.push_back(&obect);
    else {
        if (childObjects[0] == nullptr)
            childObjects[0] = &obect;
        else {
            childObjects.push_back(&obect);
        }
    }
    return childObjects.size();
}

std::vector<TObjectOfObservation*> TObjectOfObservation::GetChildObject() {
    return childObjects;
}

void TObjectOfObservation::AddNeighboringObject(TObjectOfObservation& obect) {
    neighboringObject.push_back(&obect);
}

void TObjectOfObservation::ExcludeChildObject(TObjectOfObservation& obect) {
    auto item = std::find(childObjects.begin(), childObjects.end(), &obect);
    childObjects.erase(item);
}

void TObjectOfObservation::Update() {
    for (auto& elem : childObjects)
        elem->Update();
}

std::vector<IProperties*>& TObjectOfObservation::GetAllProperties() {
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
