#include "Tag.h"
#include <iostream>

using namespace std;

Tag::Tag()
{
    toBeRemoved = false;
    parent = NULL;
    label = "";
    content = "";
}

Tag::~Tag()
{
    for (list<Tag*>::iterator it = children.begin(); it != children.end();)
    {
        delete *it;
        it = children.erase(it);
    }

    children.clear();
}

void Tag::remove()
{
    toBeRemoved = true;

    if (parent == NULL)
    {
        cerr << "Trying to remove tag with no parent." << endl;
        return;
    }

    parent->refresh();
}

void Tag::refresh()
{
    if (! children.empty())
    {
        for (list<Tag*>::iterator it = children.begin(); it != children.end();)
        {
            if ((*it)->getToBeRemoved())
            {
                delete *it;
                it = children.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}

void Tag::addChild(Tag *newTag)
{
    children.push_back(newTag);

    newTag->setParent(this);
}

Tag *Tag::getFirstChild() const
{
    if (children.empty())
    {
        return NULL;
    }

    return children.front();
}

Tag *Tag::getSibling() const
{
    list<Tag*> siblings = parent->getChildren();
    if (siblings.size() == 1)
    {
        return NULL;
    }

    list<Tag*>::iterator it = siblings.begin();
    while (*it != this) it++;
    it++;

    if (it == siblings.end())
    {
        return siblings.front();
    }

    return *it;
}

Tag *Tag::getParent() const
{
    return parent;
}

void Tag::setParent(Tag *p)
{
    parent = p;
}

list<Tag*> Tag::getChildren() const
{
    return children;
}

std::string Tag::getContent() const
{
    return content;
}

void Tag::setContent(string c)
{
    content = c;
}

std::string Tag::getLabel() const
{
    return label;
}

bool Tag::getToBeRemoved() const
{
    return toBeRemoved;
}

void Tag::errorOnSet(string attName, int value, errorType type) const
{
    cerr << "Can't set attribute " << attName << " to value " << value << " on tag " << getLabel() + ". ";
    switch (type) {
    case UNKNOWN:
        cerr << "Attribute " << attName << " is unknown for this tag.";
        break;
    case NO_ATTRIBUTES:
        cerr << "This tag has no attrubutes.";
    case BAD_VALUE:
        cerr << "Value " << value << " is invalid for attribute " << attName << ".";
    default:
        break;
    }

    cerr << endl;
}

void Tag::errorOnSet(string attName, string value, errorType type) const
{
    cerr << "Can't set attribute " << attName << " to value " << value << " on tag " << getLabel() + ". ";
    switch (type) {
    case UNKNOWN:
        cerr << "Attribute " << attName << " is unknown for this tag.";
        break;
    case NO_ATTRIBUTES:
        cerr << "This tag has no attrubutes.";
    case BAD_VALUE:
        cerr << "Value " << value << " is invalid for attribute " << attName << ".";
    default:
        break;
    }

    cerr << endl;
}

void Tag::errorOnGet(string attName, errorType type) const
{
    cerr << "Can't get attribute " << attName << " on tag " << getLabel() + ". ";
    switch (type) {
    case UNKNOWN:
        cerr << "Attribute " << attName << " is unknown for this tag.";
        break;
    case NO_ATTRIBUTES:
        cerr << "This tag has no attrubutes.";
    case UNSET:
        cerr << "Attribute " << attName << " is unset.";
    default:
        break;
    }

    cerr << endl;
}
