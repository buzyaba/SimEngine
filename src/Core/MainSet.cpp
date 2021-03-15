#include "Core/MainSet.h"
#include "Core/Parameters.h"
#include "SimEngine/common.h"

#include <string.h>

// Тут надо подумать над парсингом строки, потому что сейчас любая ошибка (не
// соответствие имени проперти и значения) все уронит
void SetProperty(IObject *object, std::string nameProperty, std::string valueProperty) {
    std::vector<std::string> notProperty = { "Neighbour", "Child", "Parent", "Object" };
    if (nameProperty == "Name")
        object->SetName(valueProperty);
    else if (!std::any_of(notProperty.begin(),
                          notProperty.end(),
                          [&nameProperty](std::string prop) {
                              return nameProperty == prop;
                          })) {
        IProperties *tempProp = object->GetProperties()[nameProperty];
        if (tempProp) {
            std::vector<double> tempVal = ParseString<double>(valueProperty, " ");

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

std::string getName(const pugi::xml_node &xml_node) {
    for (pugi::xml_node iter_obj_property = xml_node.first_child(); iter_obj_property != 0;
         iter_obj_property = iter_obj_property.next_sibling()) {
        std::string nameProperty = iter_obj_property.name();
        if (nameProperty == "Name")
            return iter_obj_property.child_value();
    }
}

template <class ObjType, DLL_TYPE DllType>
void createNewObject(std::vector<ObjType *> &objectsTempVector,
                     std::vector<ObjType *> &objectsVector,
                     const pugi::xml_node &xml_node) {
    for (pugi::xml_node xml_obj_iter = xml_node.first_child(); xml_obj_iter != 0;
         xml_obj_iter = xml_obj_iter.next_sibling()) {
        std::string name = xml_obj_iter.name();
        auto result =
            std::find_if(objectsTempVector.begin(), objectsTempVector.end(), [&](auto &t) {
                return t->ClassName() == name;
            });

        if (result == std::end(objectsTempVector)) {
            objectsTempVector.push_back(Dll_Manager::LoadDLLObject<DllType>(
                Dll_Manager::findDLLPath(getPath("/assets/models/" + name))));
            result = std::prev(objectsTempVector.end());
        }

        /// Создаем новые статические объекты
        ObjType *newObject = (*result)->Clone();
        for (pugi::xml_node iter_obj_property = xml_obj_iter.first_child(); iter_obj_property != 0;
             iter_obj_property = iter_obj_property.next_sibling()) {
            std::string nameProperty = iter_obj_property.name();
            std::string valueProperty = iter_obj_property.child_value();
            SetProperty(newObject, nameProperty, valueProperty);
        }
        objectsVector.push_back(newObject);
    }
}

TMainSet::TMainSet(std::string xmlMainSetConfigurationFile) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlMainSetConfigurationFile.c_str());
    if (result.status != pugi::status_ok)
        return;
    pugi::xml_node config = doc.child("config");

    createObjects(config);

    addDependentObjects(config);
}

void TMainSet::createObjects(const pugi::xml_node &config) {
    std::vector<TObjectOfObservation *> ObjectOfObservations;
    std::vector<TStaticObject *> StaticObjects;
    std::vector<TSmartThing *> SmartThings;

    for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling()) {
        std::string obj_type = iter.name();

        if (obj_type == "StaticObject") {
            createNewObject<TStaticObject, STATIC_OBJECT>(StaticObjects,
                                                          staticObjects,
                                                          iter);
        }
        else if (obj_type == "ObjectOfObservation") {
            createNewObject<TObjectOfObservation, OBJECT_OF_OBSERVATION>(ObjectOfObservations,
                                                                         objects,
                                                                         iter);
        }
        else if (obj_type == "SmartThing") {
            createNewObject<TSmartThing, SMART_THING>(SmartThings, things, iter);
        }
    }
}

void TMainSet::addDependentObjects(const pugi::xml_node &config) {
    for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling()) {
        std::string obj_type = iter.name();
        if (obj_type == "ObjectOfObservation") {
            for (pugi::xml_node obj_of_observe_iter = iter.first_child(); obj_of_observe_iter != 0;
                 obj_of_observe_iter = obj_of_observe_iter.next_sibling()) {
                std::string name = getName(obj_of_observe_iter);

                auto object = std::find_if(objects.begin(), objects.end(), [&](auto &t) {
                    return t->GetName() == name;
                });

                if (object != std::end(objects)) {
                    for (pugi::xml_node iter_obj_property = obj_of_observe_iter.first_child();
                         iter_obj_property != 0;
                         iter_obj_property = iter_obj_property.next_sibling()) {
                        std::string nameProperty = iter_obj_property.name();
                        std::string valueProperty = iter_obj_property.child_value();
                        if (nameProperty == "Neighbour") {
                            auto objNeighbour =
                                std::find_if(objects.begin(), objects.end(), [&](auto &t) {
                                    return t->GetName() == valueProperty;
                                });
                            (*object)->AddNeighboringObject(**objNeighbour);
                        }
                        else if (nameProperty == "Child") {
                            auto objChild =
                                std::find_if(objects.begin(), objects.end(), [&](auto &t) {
                                    return t->GetName() == valueProperty;
                                });
                            (*object)->AddChildObject(**objChild);
                        }
                        else if (nameProperty == "Parent") {
                            auto objParent =
                                std::find_if(objects.begin(), objects.end(), [&](auto &t) {
                                    return t->GetName() == valueProperty;
                                });
                            (*object)->AddParentObject(**objParent);
                        }
                    }
                }
            }
        }
        else if (obj_type == "SmartThing") {
            for (pugi::xml_node smart_thing_iter = iter.first_child(); smart_thing_iter != 0;
                 smart_thing_iter = smart_thing_iter.next_sibling()) {
                std::string name = getName(smart_thing_iter);

                auto thing = std::find_if(things.begin(), things.end(), [&](auto &t) {
                    return t->GetName() == name;
                });

                if (thing != std::end(things)) {
                    for (pugi::xml_node iter_obj_property = smart_thing_iter.first_child();
                         iter_obj_property != 0;
                         iter_obj_property = iter_obj_property.next_sibling()) {
                        std::string nameProperty = iter_obj_property.name();
                        std::string valueProperty = iter_obj_property.child_value();
                        if (nameProperty == "Object") {
                            auto observe_object =
                                std::find_if(objects.begin(), objects.end(), [&](auto &t) {
                                    return t->GetName() == valueProperty;
                                });
                            (*thing)->AddObject(**observe_object);
                            break;
                        }
                    }
                }
            }
        }
    }
}

std::vector<TObjectOfObservation *> TMainSet::GetObjects() {
    return objects;
}

std::vector<TStaticObject *> TMainSet::GetStaticObjects() {
    return staticObjects;
}

std::vector<TSmartThing *> TMainSet::GetThings() {
    return things;
}
