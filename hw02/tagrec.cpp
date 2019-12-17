#include "tagrec.h"
#include <sstream>

using namespace std;

TagRec::TagRec()
{
    fillSet = false;
    heightSet = false;
    widthSet = false;
    label = "rec";
}

string TagRec::toString() const
{
    if (! (fillSet || heightSet || widthSet))
    {
        return ONLY_TAG;
    }

    stringstream rval;
    rval << "<" << getLabel() << " ";
    if (heightSet)
    {
        rval << "height = \"" << height << "\" ";
    }

    if (widthSet)
    {
        rval << "width = \"" << width << "\" ";
    }

    if (fillSet)
    {
        rval << "fill = \"" << fill << "\" ";
    }

    rval << "/>\n";

    return rval.str();
}

void TagRec::setAttribute(string attName, int value)
{
    if (attName == "height")
    {
        if (value >= 0) {
            height = value;
            heightSet = true;
        }
        else
        {
            errorOnSet(attName, value, BAD_VALUE);
        }
        return;
    }

    if (attName == "width")
    {
        if (value >= 0) {
            width = value;
            widthSet = true;
        }
        else
        {
            errorOnSet(attName, value, BAD_VALUE);
        }
        return;
    }

    errorOnSet(attName, value, UNKNOWN);
}

void TagRec::setAttribute(string attName, string value)
{
    if (attName == "fill")
    {
        fill = value;
        fillSet = true;
        return;
    }

    errorOnSet(attName, value, UNKNOWN);
}

int TagRec::getIntAtribute(string attName) const
{
    if (attName == "height")
    {
        if (heightSet) {
            return height;
        }
        errorOnGet(attName, UNSET);
        return -1;
    }

    if (attName == "width")
    {
        if (widthSet) {
            return width;
        }
        errorOnGet(attName, UNSET);
        return -1;
    }

    errorOnGet(attName, UNKNOWN);
    return -1;
}

string TagRec::getStringAttName(string attName) const
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
