#ifndef TAG_H
#define TAG_H
#include <list>
#include <string>

#define ONLY_TAG "<" + getLabel() + "/>\n"
#define BEGIN_TAG "<" + getLabel() + ">\n"
#define END_TAG "</" + getLabel() + ">\n"

class Tag
{
private:
    Tag* parent;
    std::list<Tag*> children;
    std::string content;
    bool toBeRemoved;
protected:
    std::string label;

public:
    /**
     * @brief Tag constructor.
     */
    Tag();

    /**
     * @brief Tag virtual destructor.
     */
    virtual ~Tag();

    /**
     * @brief Removes tag (with all its children) from parent.
     */
    void remove();

    /**
     * @brief Add newTag as child of tag.
     * @param newTag tag to add
     */
    void addChild(Tag *newTag);

    /**
     * @brief Returns first child of tag. If tag has no children returns NULL.
     * @return firts child
     */
    Tag* getFirstChild() const;

    /**
     * @brief Returns next sibling of tag. If tag has no siblings returns NULL.
     * @return next sibling
     */
    Tag* getSibling() const;

    /**
     * @brief Removes all child tags that are set to be removed.
     */
	void refresh();
	
    /**
     * @brief Returns tag as string.
     * @return tag in string
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Sets attribute of name attName to value.
     * @param attName name of attribute to be set
     * @param value value to be set
     */
    virtual void setAttribute(std::string attName, std::string value) = 0;

    /**
     * @brief Sets attribute of name attName to value.
     * @param attName name of attribute to be set
     * @param value value to be set
     */
    virtual void setAttribute(std::string attName, int value) = 0;

    /**
     * @brief Returns value of int attribute with name attName.
     * @param attName name of attribute
     * @return int value
     */
    virtual int getIntAtribute(std::string attName) const = 0;

    /**
     * @brief Returns value of string attribute with name attName.
     * @param attName name of attribute
     * @return string value
     */
    virtual std::string getStringAttName(std::string attName) const = 0;

    /* getters and setters */

    void setContent(std::string c);
    Tag* getParent() const;
    void setParent(Tag *p);
    std::list<Tag*> getChildren() const;
    std::string getContent() const;
    std::string getLabel() const;
    bool getToBeRemoved() const;
    
protected:
    typedef enum {
        UNKNOWN, NO_ATTRIBUTES, UNSET, BAD_VALUE
    } errorType;
    void errorOnSet(std::string attName, int value, errorType type) const;
    void errorOnSet(std::string attName, std::string value, errorType type) const;
    void errorOnGet(std::string attName, errorType type) const;
};

#endif // TAG_H
