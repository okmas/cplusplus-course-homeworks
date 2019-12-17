#ifndef CREATURE_H
#define CREATURE_H

#include "card.h"
#include "land.h"

class Creature : public Card
{
private:
    // help enum used for indexing in arrays
    typedef enum {
        C_RED = 0, C_GREEN = 1, C_WHITE = 2, C_BLACK = 3, C_BLUE = 4
    } color;

    unsigned int attack;
    unsigned int defence;
    bool summoningSickness; // true if the creature has been summoned in this round
    unsigned int cost[5]; // amounts of mana needed to buy the creature
public:
    /**
     * @brief Constructor.
     */
    Creature();

    /**
     * @brief Method used to play a card of type creature.
     */
    void summon();

    /**
     * @brief Heals the creature from summoning sicknes.
     */
    void prepare();

    /**
     * @brief Getter for attribute summoningSickness.
     * @return true if sick, false otherwise
     */
    bool justSummoned() const;

    /**
     * @brief Getter for attribute attack.
     * @return creature's attack
     */
    unsigned int getAttack() const;

    /**
     * @brief Getter for attribute defence.
     * @return creature's defence
     */
    unsigned int getDefence() const;

    /**
     * @brief Returns the total cost of the creature.
     * @return total cost
     */
    unsigned int getTotalCost() const;

    /**
     * @brief Returns cost of the creature of specific mana color.
     * @param color color of mana
     * @return special cost
     */
    unsigned int getSpecialCost( const mana color ) const;
};

#endif // CREATURE_H
