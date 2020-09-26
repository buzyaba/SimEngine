#include "TrafficLight.hpp"

LIB_EXPORT_API TSmartThing* create()
{
    return new TTrafficLight("TTrafficLight");
}
