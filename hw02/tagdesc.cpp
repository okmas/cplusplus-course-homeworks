#include "tagdesc.h"
#include <iostream>

using namespace std;

string TagDesc::toString() const
{
    if (getContent() == "")
    {
        return ONLY_TAG;
    }

    return BEGIN_TAG + getContent() + '\n' + END_TAG;
}

int TagDesc::getIntAtribute(string attName) const
{
    errorOnGet(attName, NO_ATTRIBUTES);
    return -1;
}

void TagDesc::setAttribute(string attName, int value)
{
    errorOnSet(attName, value, NO_ATTRIBUTES);
}

string TagDesc::getStringAttName(string attName) const
{
    errorOnGet(attName, NO_ATTRIBUTES);
    return "";
}

void TagDesc::setAttribute(string attName, string value)
{
    errorOnSet(attName, value, NO_ATTRIBUTES);
}
