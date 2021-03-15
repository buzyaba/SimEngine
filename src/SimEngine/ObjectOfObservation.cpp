#include <algorithm>
#include <stdexcept>
#include "SimEngine/ObjectOfObservation.h"

TObjectOfObservation::TObjectOfObservation(std::string _name,
                                           std::vector<TObjectOfObservation*> _neighboringObject,
                                           TObjectOfObservation* _parentObject,
                                           TObjectOfObservation* _childObject)
        : TObject(_name) {
    if (_neighboringObject.size() == 1) {
        if (_neighboringObject[0] != nullptr)
            neighboringObjects = _neighboringObject;
    }
    else
        neighboringObjects = _neighboringObject;

    parentObject = _parentObject;

    if (_childObject != nullptr) {
        childObjects.push_back(_childObject);
    }
}

TObjectOfObservation::TObjectOfObservation(const TObjectOfObservation& obj) : TObject(obj) {
    this->neighboringObjects = obj.neighboringObjects;
    this->childObjects = obj.childObjects;
    this->parentObject = obj.parentObject;
}

void TObjectOfObservation::AddParentObject(TObjectOfObservation* object) {
    parentObject = object;
}

int TObjectOfObservation::AddChildObject(TObjectOfObservation* object) {
    if (childObjects.size() == 0)
        childObjects.push_back(object);
    else {
        if (childObjects[0] == nullptr)
            childObjects[0] = object;
        else {
            if (std::end(childObjects) !=
                std::find(childObjects.begin(), childObjects.end(), object))
                childObjects.push_back(object);
        }
    }
    return childObjects.size();
}

std::vector<TObjectOfObservation*> TObjectOfObservation::GetChildObjects() {
    return childObjects;
}

std::vector<TObjectOfObservation*> TObjectOfObservation::GetNeighboringObjects() {
    return neighboringObjects;
}

TObjectOfObservation* TObjectOfObservation::GetParentObject() {
    return parentObject;
}

TObjectOfObservation* TObjectOfObservation::GetChildObjects(std::string name) {
    auto res =
        std::find_if(childObjects.begin(), childObjects.end(), [&name](TObjectOfObservation* obj) {
            return name == obj->GetName();
        });
    if (res != std::end(childObjects))
        return *res;
    else
        std::runtime_error("No child object with name: " + name);
}

TObjectOfObservation* TObjectOfObservation::GetNeighboringObject(std::string name) {
    auto res =
        std::find_if(neighboringObjects.begin(), neighboringObjects.end(), [&name](TObjectOfObservation* obj) {
            return name == obj->GetName();
        });
    if (res != std::end(neighboringObjects))
        return *res;
    else
        std::runtime_error("No neighboring object with name: " + name);
}

void TObjectOfObservation::AddNeighboringObject(TObjectOfObservation* object) {
    if (std::find(neighboringObjects.begin(), neighboringObjects.end(), object) !=
        std::end(neighboringObjects)) {
        neighboringObjects.push_back(object);
        object->AddNeighboringObject(this);
    }
}

void TObjectOfObservation::ExcludeChildObject(TObjectOfObservation* object) {
    auto item = std::find(childObjects.begin(), childObjects.end(), object);
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
