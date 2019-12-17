#ifndef LAND_H
#define LAND_H

#include "card.h"

// types of land cards - each produces different color of mana
typedef enum {
    PLAINS, ISLAND, SWAMP, MOUNTAIN, FOREST
} landType;

// colors of mana
typedef enum {
     WHITE, BLUE, BLACK, RED, GREEN, NONE
} mana;

class Land : public Card
{
private:
    landType type;
public:
    /**
     * @brief Constructor.
     */
    Land();

    /**
     * @brief Getter for attribute type.
     * @return land type
     */
    landType getType() const;

    /**
     * @brief Makes the land to produce mana, card is tapped.
     * @return produced mana
     */
    mana getMana();
};

#endif // LAND_H
