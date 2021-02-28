TSmartThingSchedule::TSmartThingSchedule(std::vector<IObject*> _objects, std::string xmlName) : 
  TExternalActionSchedule(_objects, xmlName) {}

void TSmartThingSchedule::UpdateObjectsProperties(std::size_t time)
{

  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      auto& thingActuators = static_cast<TSmartThing*>(objects[i])->GetActuators();
      if (objectPropertyIntervals.size() > 0)
      {
        for (auto& elem : objectPropertyIntervals[i])
        {
          if (elem.second.isSet)
          {
            try {
              std::map<std::string, double>& tmp = elem.second.GetValue(time);
              properties[elem.first]->SetValues(tmp);
            } catch (...) {}
          }
        }
      }
    }
  }
}