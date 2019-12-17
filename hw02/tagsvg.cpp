#include "tagsvg.h"
#include <list>
#include <sstream>
#include <iostream>

using namespace std;

string TagSvg::toString() const
{
    if (getChildren().size() == 0)
    {
        return ONLY_TAG;
    }

    return BEGIN_TAG + childrenToString() + END_TAG;
}

string TagSvg::childrenToString() const
{
    stringstream rval;
    list<Tag*> children = getChildren();

    if (! children.empty())
    {
        for (list<Tag*>::iterator it = children.begin();
             it != children.end(); it++)
        {
            rval << (*it)->toString();
        }

        return rval.str();
    }
    cout << "HA";
    return "";
}

int TagSvg::getIntAtribute(string attName) const
{
    errorOnGet(attName, NO_ATTRIBUTES);
    return -1;
}

void TagSvg::setAttribute(string attName, int value)
{
    errorOnSet(attName, value, NO_ATTRIBUTES);
}

string TagSvg::getStringAttName(string attName) const
{
    errorOnGet(attName, NO_ATTRIBUTES);
    return "";
}

void TagSvg::setAttribute(string attName, string value)
{
    errorOnSet(attName, value, NO_ATTRIBUTES);
}
