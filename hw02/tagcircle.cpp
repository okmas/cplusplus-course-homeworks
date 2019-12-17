#include "tagcircle.h"
#include <sstream>

using namespace std;

TagCircle::TagCircle()
{
    fillSet = false;
    cxSet = false;
    cySet = false;
    rSet = false;
    label = "circle";
}

string TagCircle::toString() const
{
    if (! (fillSet || cxSet || cySet || rSet))
    {
        return ONLY_TAG;
    }

    stringstream rval;
    rval << "<" << getLabel() << " ";
    if (cxSet)
    {
        rval << "cx = \"" << cx << "\" ";
    }

    if (cySet)
    {
        rval << "cy = \"" << cy << "\" ";
    }

    if (rSet)
    {
        rval << "r = \"" << r << "\" ";
    }

    if (fillSet)
    {
        rval << "fill = \"" << fill << "\" ";
    }

    rval << "/>\n";

    return rval.str();
}

void TagCircle::setAttribute(string attName, int value)
{
    if (attName == "cx")
    {
        cx = value;
        cxSet = true;
        return;
    }

    if (attName == "cy")
    {
        cy = value;
        cySet = true;
        return;
    }

    if (attName == "r")
    {
        if (value >= 0) {
            r = value;
            rSet = true;
        }
        else
        {
            errorOnSet(attName, value, BAD_VALUE);
        }
        return;
    }

    errorOnSet(attName, value, UNKNOWN);
}

void TagCircle::setAttribute(string attName, string value)
{
    if (attName == "fill")
    {
        fill = value;
        fillSet = true;
        return;
    }

    errorOnSet(attName, value, UNKNOWN);
}

int TagCircle::getIntAtribute(string attName) const
{
    if (attName == "cx")
    {
        if (cxSet) {
            return cx;
        }
        errorOnGet(attName, UNSET);
        return - 1;
    }

    if (attName == "cy")
    {
        if (cySet) {
            return cy;
        }
        errorOnGet(attName, UNSET);
        return - 1;
    }

    if (attName == "r")
    {
        if (rSet) {
            return r;
        }
        errorOnGet(attName, UNSET);
        return - 1;
    }

    errorOnGet(attName, UNKNOWN);
    return -1;
}

string TagCircle::getStringAttName(string attName) const
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
