#include "CarDestroyer.hpp"

void TCarDestroyer::Update()
{
	auto&& isBblockieren = this->properties["IsBblockieren"]->GetValues();
	isBblockieren["IsBblockieren"] = 0;
	this->properties["IsBblockieren"]->SetValues(isBblockieren);

	for (int i = 0; i < this->childObjects.size(); i++)
	{
		TObjectOfObservation* child = this->childObjects[i];
		if (child != nullptr)
		{
			this->ExcludeChildObject(*child);
			delete child;
		}
	}
}

TCarDestroyer::TCarDestroyer(std::string _name) : TRoad(_name)
{

}

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCarDestroyer("TCarDestroyer");
}
