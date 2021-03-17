#include "SimEngine/Sensor.h"

TSensor::TSensor(std::string _name) : packet(nullptr) {
    SetName(_name);
    oldObjectCount = 0;
    propertyCount = 0;
}

TSensor::TSensor(const TSensor& sensor) {
    this->packet = sensor.packet;
    this->name = sensor.name;
    this->objects = sensor.objects;
    this->oldObjectCount = sensor.oldObjectCount;
    this->propertyCount = sensor.propertyCount;
}

void TSensor::UpdateObjectsCount() {
    if (oldObjectCount != objects.size()) {
        oldObjectCount = objects.size();
        vals.resize(oldObjectCount);
        propertyCount = 0;
        for (size_t i = 0; i < objects.size(); ++i) {
            if (objects[i] != nullptr) {
                objectsProperties[i] = objects[i]->GetProperties();
                for (auto& elem : objectsProperties[i])
                    if (elem.second != nullptr && elem.second->IsObserved())
                        for (auto& iter : elem.second->GetValues())
                            ++propertyCount;
            }
        }
    }
}

TDataPacket& TSensor::GetDataPacket() {
    if (packet == nullptr)
        packet = new TDataPacket(propertyCount * sizeof(double));

    packet->SetSize(propertyCount * sizeof(double));
    double* data = packet->GetData<double>();
    size_t t = 0;
    for (size_t i = 0; i < objectsProperties.size(); ++i) {
        for (auto& elem : objectsProperties[i])
            if (elem.second != nullptr && elem.second->IsObserved())
                for (auto& iter : elem.second->GetValues())
                    data[t++] = iter.second;
    }

    return *packet;
}

void TSensor::AddObject(TObjectOfObservation* object) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i] == object)
            return;
    }
    objects.push_back(object);
    objectsProperties.resize(objects.size());
    UpdateObjectsCount();
}

void TSensor::ExcludeObject(TObjectOfObservation* object) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i] == object) {
            objects[i] = nullptr;
            auto it = std::remove(objects.begin(), objects.end(), nullptr);
            objects.resize(it - objects.begin());
            objectsProperties.resize(objects.size());
            UpdateObjectsCount();
            return;
        }
    }
}

void TSensor::ExcludeObject(std::string objectName) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i] != nullptr) {
            if (objects[i]->GetName() == objectName) {
                objects[i] = nullptr;
            auto it = std::remove(objects.begin(), objects.end(), nullptr);
            objects.resize(it - objects.begin());
            objectsProperties.resize(objects.size());
            UpdateObjectsCount();
            return;
            }
        }
    }
}

std::string TSensor::GetName() {
    return name;
}

void TSensor::SetName(std::string _name) {
    if (_name.length() > 0)
        name = _name;
    else
        throw -1;
}
