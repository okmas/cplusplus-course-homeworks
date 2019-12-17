#ifndef IOOPERATION_H
#define IOOPERATION_H
#include "Tag.h"
#include <iostream>
#include <fstream>

class IOoperation
{
public:
    IOoperation();
public:
    /**
     * @brief Saves svg file pointed by tag to file filename.
     * @param filename name of file to save content of tag to
     * @param tag pointer to root node of svg
     */
    void save(std::string filename, Tag* tag);

    /**
     * @brief Loads svg file.
     * @param filename name of file to load
     * @return pointer to root node of svg
     */
    Tag* load(std::string filename);

private:
    typedef enum {
        ROOT, DESC, CIRCLE, REC, G, UNKNOWN_NODE
    } nodeType;
    typedef enum {
        BEGIN, BEGIN_UNITARY, END, EMPTY, EMPTY_BINARY, UNKNOWN_TYPE
    } tagType;

    bool step(std::ifstream &input, std::string &s, tagType &t, nodeType &n);
    std::string nextTag(std::ifstream &input);
    tagType getTagType(std::string next);
    nodeType getNodeType(std::string next);
    std::string nextToNodeString(std::string s);

    void loopThroughChildren(std::ifstream &input, std::string &next,
                             Tag *parent);
    void setAttributes(std::ifstream &input, std::string &s, Tag *parent);

    void handleEmptyNode(Tag *parent, std::string next);

    void addDesc(std::ifstream &input, Tag *parent);
    void addCircle(std::ifstream &input, Tag *parent, std::string s);
    void addRec(std::ifstream &input, Tag *parent, std::string s);
    void addG(std::ifstream &input, Tag *parent, std::string s);

    void printNext(std::string next, tagType t, nodeType n);
    std::string nodeToString(nodeType n);
    std::string tagToString(tagType t);
};

#endif // IOOPERATION_H
