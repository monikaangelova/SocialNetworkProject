#include "Unique.h"
unsigned Unique::genetateId()
{
    globalId++;
    return globalId;
}
void Unique::setGlobalId(unsigned id)
{
    globalId = id;
}
unsigned Unique::globalId = 0;