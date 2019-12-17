#ifndef TAGDESC_H
#define TAGDESC_H

#include "Tag.h"

class TagDesc : public Tag
{
public:
    /**
     * @brief TagDesc constructor.
     */
    TagDesc() { label = "desc"; }

    /**
     * @brief Returns description tag as string.
     * @return description tag in string
     */
    virtual std::string toString() const;

    /**
     * @brief Sets attribute of name attName to value.
     * @param attName name of attribute to be set
     * @param value value to be set
     */
    virtual void setAttribute(std::string attName, std::string value);

    /**
     * @brief Sets attribute of name attName to value.
     * @param attName name of attribute to be set
     * @param value value to be set
     */
    virtual void setAttribute(std::string attName, int value);

    /**
     * @brief Returns value of int attribute with name attName.
     * @param attName name of attribute
     * @return int value
     */
    virtual int getIntAtribute(std::string attName) const;

    /**
     * @brief Returns value of string attribute with name attName.
     * @param attName name of attribute
     * @return string value
     */
    virtual std::string getStringAttName(std::string attName) const;
};

#endif // TAGDESC_H
