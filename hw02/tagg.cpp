#include "tagg.h"
#include <list>
#include <sstream>
#include <iostream>

using namespace std;

TagG::TagG()
{
    fillSet = false;
    label = "g";
}

string TagG::toString() const
{
    stringstream rval;
    rval << "<" + getLabel();

    if (fillSet)
    {
        rval << " fill = \"" << fill << "\" ";
    }

    if (getChildren().empty())
    {
        rval << "/>\n";
    }
    else
    {
        rval << ">\n"
             << childrenToString() << END_TAG;
    }

    return rval.str();
}

string TagG::childrenToString() const
{
    stringstream rval;
    list<Tag*> children = getChildren();

    for (list<Tag*>::iterator it = children.begin(); it != children.end(); it++)
    {
        rval << (*it)->toString();
    }

    return rval.str();
}

void TagG::setAttribute(string attName, int value)
{
    errorOnSet(attName, value, UNKNOWN);
}

void TagG::setAttribute(string attName, string value)
{
    if (attName == "fill")
    {
        fill = value;
        fillSet = true;
        return;
    }

    errorOnSet(attName, value, UNKNOWN);
}

int TagG::getIntAtribute(string attName) const
{
    errorOnGet(attName, UNKNOWN);
    return -1;
}

string TagG::getStringAttName(string attName) const
{
    if (attName == "fill")
    {
        if (fillSet)
        {
            return fill;
        }
        errorOnGet(attName, UNSET);
        return "";
    }

    errorOnGet(attName, UNKNOWN);
    return "";
}
