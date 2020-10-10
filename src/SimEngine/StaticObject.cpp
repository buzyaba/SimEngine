#include "SimEngine/StaticObject.h"

TStaticObject::TStaticObject(std::string _name) : TObject(_name) {
}

// TStaticObject* TStaticObject::Clone()
// {
//   return new TStaticObject(*this);
// }

// TScene::TScene(std::string _name) : TObject(_name)
// {
// }

// TScene::TScene(const TScene& _scene) : TObject(_scene)
// {
//   this->objectsOfObservation = _scene.objectsOfObservation;
//   this->smartThings = _scene.smartThings;
//   this->scenes = _scene.scenes;
// }

// void TScene::AddObject(TObjectOfObservation& obect)
// {
//   objectsOfObservation.push_back(&obect);
// }

// void TScene::AddThing(TSmartThing& obect)
// {
//   smartThings.push_back(&obect);
// }

// void TScene::ExcludeObject(TObjectOfObservation& obect)
// {
//   for (int i = 0; i < objectsOfObservation.size(); i++)
//   {
//     if (objectsOfObservation[i] == &obect)
//     {
//       objectsOfObservation[i] = nullptr;
//       ///Дописать перепаковку
//     }
//   }
// }

// void TScene::AddSceneObject(TScene& obect)
// {
//   scenes.push_back(&obect);
// }

// void TScene::ExcludeSceneObject(TScene& obect)
// {
//   for (int i = 0; i < objectsOfObservation.size(); i++)
//   {
//     if (scenes[i] == &obect)
//     {
//       scenes[i] = nullptr;
//       ///Дописать перепаковку
//     }
//   }
// }
