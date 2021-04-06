#include "DummySmartThing.h"

LIB_EXPORT_API TSmartThing* create()
{
    return new TDummySmartThing("TDummySmartThing");
}
