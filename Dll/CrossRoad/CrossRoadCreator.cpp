#include "CrossRoad.hpp"

LIB_EXPORT_API TObjectOfObservation* create()
{
    return new TCrossRoad("TCrossRoad");
}
