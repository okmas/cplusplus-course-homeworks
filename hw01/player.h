#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "land.h"

#define CREATURES_COUNT 8
#define LANDS_COUNT 10
#define MANA_COUNT 5

class Player
{
private:
    // help enum used for indexing in arrays
    typedef enum {
        C_RED = 0, C_GREEN = 1, C_WHITE = 2, C_BLACK = 3, C_BLUE = 4
    } color;

    const char *name;
    Creature creatures[CREATURES_COUNT];
    Land lands[LANDS_COUNT];
    int life;
    unsigned int ownedMana[MANA_COUNT];
public:
    /**
     * @brief Constructor that initializes player's name.
     * @param name name to be set as player's
     */
    Player( const char* name );

    /**
     * @brief Constructor that initializes player's name and life.
     * @param name name to be set as player's
     * @param life initial life of player
     */
    Player( const char* name, const unsigned int life );

    /**
     * @brief Getter for attribute name.
     * @return player's name
     */
    const char* getName() const;

    /**
     * @brief Getter for attribute life.
     * @return player's life
     */
    int getLife() const;

    /**
     * @brief Performs one turn in FI-MAGIC.
     * @param opponent opponent of this player in game
     */
    void oneTurn( Player& opponent );

    /**
     * @brief Prints all important info about the player.
     */
    void printInfo() const;
private:
    void prepareCreatures();
    void prepareLands();
    int landToBePlayed();
    void playLandCard( const unsigned int index );
    void init( const char *name, const unsigned int life );
    int indexOfMana( const mana m ) const;
    void incMana( const mana newMana );
    void incManaByType( const landType t );
    void payForCreature(    const Creature &c );
    bool canBuyCreature( const Creature &c ) const;
    void summonCreatures();
    void playCreature( Creature &c );
    void createMana();
    void attackOpponent( Player &opponent );
    bool creatureReadyToAttack( const Creature &c ) const;
    void handleOpponentAttack( const Creature &c );
    bool creatureCanDefend( const Creature &c ) const;
};

#endif // PLAYER_H
