#include "IOoperation.h"
#include "tagcircle.h"
#include "tagrec.h"
#include "tagdesc.h"
#include "tagg.h"
#include "tagsvg.h"
#include <locale>
#include <iomanip>
#include <cstdlib>

using namespace std;

IOoperation::IOoperation() {}

void IOoperation::save(std::string filename, Tag *tag)
{
    ofstream output(filename.c_str());

    if (! output.is_open())
    {
        cerr << "Unable to wirte to file " << filename << "." << endl;
        return;
    }

    if (tag == NULL)
    {
        cerr << "Root tag cannot be NULL." << endl;
        return;
    }

    output << tag->toString();

    output.close();
}

Tag *IOoperation::load(std::string filename)
{
    ifstream input(filename.c_str());

    if (! input.is_open())
    {
        cerr << "Unable to read file " << filename << "." << endl;
        return NULL;
    }

    TagSvg *rootTag;
    string next;
    tagType tagT;
    nodeType nodeT;

    // loading root tag
    step(input, next, tagT, nodeT);
    rootTag = new TagSvg();

    // loop
    loopThroughChildren(input, next, rootTag);

    input.close();
    return rootTag;
}

bool IOoperation::step(ifstream &input, string &s, tagType &t, nodeType &n)
{
    s = nextTag(input);
    t = getTagType(s);
    if (t == UNKNOWN_TYPE) n = UNKNOWN_NODE;
    else n = getNodeType(s);

    if (n == UNKNOWN_NODE && t != END) t = UNKNOWN_TYPE;

    return t != END/* || n != ROOT)*/ && t != UNKNOWN_TYPE;
}

string IOoperation::nextTag(ifstream &input)
{
    string next;
    input >> next;
    return next;
}

IOoperation::tagType IOoperation::getTagType(string next)
{
    string tagName = nextToNodeString(next);

    if (">" == next) return END;
    if ("/>" == next) return END;
    if ("<" + tagName + ">" == next) return BEGIN;
    if ("<" + tagName == next) return BEGIN_UNITARY;
    if ("</" + tagName + ">" == next) return END;
    if ("<" + tagName + "/>" == next) return EMPTY;
    if ("<" + tagName + "></" + tagName + ">" == next) return EMPTY_BINARY;
    if ("></" + tagName + ">" == next) return END;

    return UNKNOWN_TYPE;
}

IOoperation::nodeType IOoperation::getNodeType(string next)
{
    string nodeName = nextToNodeString(next);

    if (nodeName == "svg") return ROOT;
    if (nodeName == "desc") return DESC;
    if (nodeName == "circle") return CIRCLE;
    if (nodeName == "rec") return REC;
    if (nodeName == "g") return G;

    return UNKNOWN_NODE;
}

string IOoperation::nextToNodeString(string s)
{
    if (s.length() < 2) return "";

    unsigned int from = 0;
    int to = s.length() - 1;
    while (from < s.length() && ! isalpha(s[from])) from++;
    while (to >= 0 && ! isalpha(s[to])) to--;

    if (from == s.length()) return "";

    s = s.substr(from, to - from + 1);

    // checking for EMPTY_BINARY tag
    if (s.length() >= 5)
    {
        from = 0;
        while (from < s.length() && ! isalpha(s[from])) from++;
        if (from != s.length())
        {
            if (s.substr(0, s.length() / 2 - 1) ==
                    s.substr(s.length() - s.length() / 2 + 1) &&
                    s.substr(s.length() / 2 - 1, 3) == "></")
                return s.substr(0, s.length() / 2 - 1);
        }
    }

    return s;
}

void IOoperation::loopThroughChildren(ifstream &input, string &next,
                                      Tag *parent)
{
    tagType tagT;
    nodeType nodeT;
    while (step(input, next, tagT, nodeT))
    {
        if (tagT == EMPTY || tagT == EMPTY_BINARY)
        {
            handleEmptyNode(parent, next);
        }
        else if (tagT == BEGIN || tagT == BEGIN_UNITARY)
        {
            switch (nodeT)
            {
            case DESC:
                addDesc(input, parent);
                break;
            case CIRCLE:
                addCircle(input, parent, next);
                break;
            case REC:
                addRec(input, parent, next);
                break;
            case G:
                addG(input, parent, next);
                break;

            default:
                cerr << "Invalid tag found: " << nodeT << endl;
                break;
            }
        }

    }
}

void IOoperation::setAttributes(ifstream &input, string &s, Tag *parent)
{
    tagType t;
    nodeType n;
    string strVal;

    step(input, s, t, n);
    while (t != END)
    {
        input >> strVal;
        input >> strVal;
        strVal = strVal.substr(1, strVal.length() - 2);

        if ((strVal[0] == '-' && strVal.length() > 1 &&
             isalnum(strVal[1]) && ! isalpha(strVal[1])) ||
                (isalnum(strVal[0]) && ! isalpha(strVal[0]))) {
            parent->setAttribute(s, atoi(strVal.c_str()));
        }
        else
        {
            parent->setAttribute(s, strVal.c_str());
        }

        step(input, s, t, n);
    }
}

void IOoperation::handleEmptyNode(Tag *parent, string next)
{
    switch(getNodeType(next))
    {
        case DESC: parent->addChild(new TagDesc()); break;
        case CIRCLE: parent->addChild(new TagCircle()); break;
        case REC: parent->addChild(new TagRec()); break;
        case G: parent->addChild(new TagG()); break;
        default :cerr << "Unknown empty binary tag: "<< nextToNodeString(next) << endl;
    }
}

void IOoperation::addDesc(ifstream &input, Tag *parent)
{
    TagDesc *newDesc = new TagDesc();
    string content;
    string help;

    getline(input, content, '<');
    input >> help;

    unsigned from = 0;
    int to = content.size() - 1;
    while (from < content.size() && isspace(content[from])) from++;
    while (to >= 0 && isspace(content[to])) to--;

    content = content.substr(from, to - from + 1);
    newDesc->setContent(content);

    parent->addChild(newDesc);
}

void IOoperation::addCircle(ifstream &input, Tag *parent, string s)
{
    TagCircle *newCircle = new TagCircle();

    setAttributes(input, s, newCircle);

    parent->addChild(newCircle);
}

void IOoperation::addRec(ifstream &input, Tag *parent, string s)
{
    TagRec *newRec = new TagRec();

    setAttributes(input, s, newRec);

    parent->addChild(newRec);
}

void IOoperation::addG(ifstream &input, Tag *parent, string s)
{
    TagG *newG = new TagG();

    if (s[s.length() - 1] != '>')
    {
        setAttributes(input, s, newG);
    }

    if ((s == ">") || (s.length() > 1 && s.substr(s.length() - 2, 2) != "/>")) {
        loopThroughChildren(input, s, newG);
    }

    parent->addChild(newG);
}

void IOoperation::printNext(string next, tagType t, nodeType n)
{
    cout << setw(17) << next
         << setw(14) << tagToString(t)
         << setw(14) << nodeToString(n)
         << endl;
}

string IOoperation::nodeToString(nodeType n)
{
    switch(n)
    {
    case ROOT: return "svg";
    case DESC: return "desc";
    case G: return "g";
    case CIRCLE: return "circle";
    case REC: return "rec";
    default: return "unknown";
    }
}

string IOoperation::tagToString(tagType t)
{
    switch (t)
    {
    case BEGIN: return "BEGIN";
    case BEGIN_UNITARY: return "BEGIN_UNITARY";
    case END: return "END";
    case EMPTY: return "EMPTY";
    case EMPTY_BINARY: return "EMPTY_BINARY";
    default: return "UNKNOWN";
    }
}
