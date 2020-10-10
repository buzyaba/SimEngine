#include "SmartSocket.h"

LIB_EXPORT_API TSmartThing* create()
{
    return new TSmartSocket("TSmartSocket");
}
