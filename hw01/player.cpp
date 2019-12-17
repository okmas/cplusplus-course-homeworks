#include "player.h"
#include <iostream>
#include <cstring>

using namespace std;

Player::Player( const char *name )
{
    init( name, 20 );
}

Player::Player( const char *name, const unsigned int life )
{
    init( name, life );
}

void Player::init( const char *name, const unsigned int life )
{
    this->name = name;
    this->life = life;
    memset( ownedMana, 0, MANA_COUNT * sizeof( unsigned int ) );
}

const char *Player::getName() const
{
    return name;
}

int Player::getLife() const
{
    return life;
}

void Player::oneTurn( Player &opponent )
{
    // untap step
    prepareCreatures();
    prepareLands();

    // getting mana for this turn
    createMana();

    // playing a land card
    int nextLand = landToBePlayed();
    if ( nextLand != -1 ) playLandCard( nextLand );

    // summoning creatures
    summonCreatures();

    // attack on opponent, defense
    attackOpponent( opponent );
}

void Player::printInfo() const
{
    cout << "Player " << name << endl << "Life: " << life << endl;

    cout << "Lands:" << endl;

    for ( size_t i = 0; i < LANDS_COUNT; i++ )
    {
        cout << i + 1 << ". ";
        landType type = lands[i].getType();
        switch ( type )
        {
            case FOREST: cout << "FOREST | "; break;
            case MOUNTAIN: cout << "MOUNTAIN | "; break;
            case ISLAND: cout << "ISLAND | "; break;
            case SWAMP: cout << "SWAMP | "; break;
            case PLAINS: cout << "PLAINS | "; break;
        }
        if ( lands[i].isPlayed() ) cout << "table";
        else cout << "hand";
        cout << endl;
    }
    cout << endl << "Creatures: " << endl;

    for ( size_t i = 0; i < CREATURES_COUNT; i++ )
    {
        cout << "Creature " << i + 1 << ".: " << "Att.: " << creatures[i].getAttack() << " | Def.: " << creatures[i].getDefence() << " | ";
        if ( creatures[i].isPlayed() )
        {
            cout << "table | ";
            if ( creatures[i].isTapped() ) cout << "tapped | ";
            if ( creatures[i].justSummoned() ) cout << "summoning sick | ";
            cout << endl;
        }
        else
        {
            cout << "hand | Cost: ";
            cout << "Total: " << creatures[i].getTotalCost() << ", W: " <<  creatures[i].getSpecialCost(WHITE)
                    << ", U: " << creatures[i].getSpecialCost(BLUE) <<  ", B: " << creatures[i].getSpecialCost(BLACK)
                        <<  ", R: " << creatures[i].getSpecialCost(RED)<< ", G: " << creatures[i].getSpecialCost(GREEN)
                            << endl;
        }
    }

    cout << endl;
}

void Player::prepareCreatures()
{
    for ( int i = 0; i < CREATURES_COUNT; i++ )
    {
        if ( creatures[i].isTapped() ) creatures[i].unTap();
        if ( creatures[i].justSummoned() ) creatures[i].prepare();
    }
}

void Player::prepareLands()
{
    for ( int i = 0; i < LANDS_COUNT; i++ )
    {
        if ( lands[i].isTapped() ) lands[i].unTap();
    }
}

void Player::createMana()
{
    memset( ownedMana, 0, MANA_COUNT * sizeof( unsigned int ) );

    for ( int i = 0; i < LANDS_COUNT; i++ )
    {
        if ( lands[i].isPlayed() && ! lands[i].isTapped() )
        {
            incMana( lands[i].getMana() );
        }
    }
}

void Player::incMana( const mana newMana )
{
    ownedMana[indexOfMana( newMana )]++;
}

int Player::indexOfMana( const mana m ) const
{
    switch ( m )
    {
        case RED: return C_RED;
        case WHITE: return C_WHITE;
        case BLUE: return C_BLUE;
        case BLACK: return C_BLACK;
        case GREEN: return C_GREEN;
        default: return -1;
    }
}

void Player::incManaByType( const landType t )
{
    int index;
    switch ( t )
    {
        case MOUNTAIN: index = C_RED; break;
        case PLAINS: index = C_WHITE; break;
        case ISLAND: index = C_BLUE; break;
        case SWAMP: index = C_BLACK; break;
        case FOREST: index = C_GREEN; break;
    }

    ownedMana[index]++;
}

int Player::landToBePlayed()
{
    unsigned int best = 0; // best sum of attack and defence of a land
    int rval = -1; // return value - index of "best" land
    bool allCardsPlayed = true;

    // finding the best land card
    for ( int i = 0; i < LANDS_COUNT; i++ )
    {
        if ( ! lands[i].isPlayed() )
        {
            allCardsPlayed = false;

            unsigned int temp = 0;
            unsigned int originalMana[MANA_COUNT];
            memcpy( originalMana, ownedMana, MANA_COUNT * sizeof( unsigned int ) );

            incManaByType( lands[i].getType() );

            for ( int j = 0; j < CREATURES_COUNT; j++ )
            {
                if ( ( ! creatures[j].isPlayed() ) && canBuyCreature( creatures[j] ) )
                {
                    payForCreature( creatures[j] );
                    temp += creatures[j].getAttack();
                    temp += creatures[j].getDefence();
                }
            }

            if ( temp > best )
            {
                best = temp;
                rval = i;
            }

            memcpy( ownedMana, originalMana, MANA_COUNT * sizeof( unsigned int ) );
        }
    }

    /* if there are non-played land cards, but none of them gives enough mana to summon a creature
       player plays a non-played card of the smallest index */
    if ( ( best == 0 ) && ( ! allCardsPlayed ) )
    {
        int i = 0;
        while ( lands[i].isPlayed() ) i++;
        rval = i;
    }

    return rval;
}

void Player::playLandCard( const unsigned int index )
{
    lands[index].play();
    incMana( lands[index].getMana() );
}

void Player::summonCreatures()
{
    for ( int i = 0; i < CREATURES_COUNT; i++ )
    {
        if ( ! creatures[i].isPlayed() && canBuyCreature( creatures[i] ) )
        {
            playCreature( creatures[i] );
        }
    }
}

bool Player::canBuyCreature( const Creature &c ) const
{
    bool rval = true;
    rval &= ( ownedMana[C_RED] >= c.getSpecialCost( RED ) );
    rval &= ( ownedMana[C_GREEN] >= c.getSpecialCost( GREEN ) );
    rval &= ( ownedMana[C_WHITE] >= c.getSpecialCost( WHITE ) );
    rval &= ( ownedMana[C_BLACK] >= c.getSpecialCost( BLACK ) );
    rval &= ( ownedMana[C_BLUE] >= c.getSpecialCost( BLUE ) );

    return rval;
}

void Player::payForCreature( const Creature &c )
{
    ownedMana[C_RED] -= c.getSpecialCost( RED );
    ownedMana[C_GREEN] -= c.getSpecialCost( GREEN );
    ownedMana[C_WHITE] -= c.getSpecialCost( WHITE );
    ownedMana[C_BLACK] -= c.getSpecialCost( BLACK );
    ownedMana[C_BLUE] -= c.getSpecialCost( BLUE );
}

void Player::playCreature( Creature &c )
{
    payForCreature( c );
    c.summon();
}

void Player::attackOpponent( Player &opponent )
{
    for ( int i = 0; i < CREATURES_COUNT; i++)
    {
        if ( creatureReadyToAttack( creatures[i] ) )
        {
            opponent.handleOpponentAttack( creatures[i] );
            creatures[i].tap();
        }
    }
}

bool Player::creatureReadyToAttack( const Creature &c ) const
{
    bool rval = true;
    rval &= c.isPlayed();
    rval &= ! c.isTapped();
    rval &= ! c.justSummoned();
    rval &= c.getAttack() >= 1;

    return rval;
}

bool Player::creatureCanDefend( const Creature &c ) const
{
    bool rval = true;
    rval &= c.isPlayed();
    rval &= ! c.isTapped();
    rval &= c.getDefence() >= 1;

    return rval;
}

void Player::handleOpponentAttack( const Creature &c )
{
    int index = -1;
    unsigned int best = 5;
    bool noCreatureCanDefend = true;

    // finding creature to defend
    for ( int i = 0; i < CREATURES_COUNT; i++ )
    {
        if ( creatureCanDefend( creatures[i] ) )
        {
            noCreatureCanDefend = false;

            if ( creatures[i].getDefence() > c.getAttack() &&
                 creatures[i].getDefence() < best )
            {
                index = i;
                best = creatures[i].getDefence();
            }
        }
    }

    // player has no creature that can defend him
    if ( noCreatureCanDefend )
    {
        life -= c.getAttack();
        return;
    }

    /* there is no creature with enough defence
       player sacrifizes the weakest creature */
    if ( index == -1 )
    {
        unsigned int smallest = 9;
        unsigned int indexOfWeakest = -1;
        for ( int i = 0; i < CREATURES_COUNT; i++ )
        {
            if ( creatures[i].getAttack() + creatures[i].getDefence() < smallest
                 && creatureCanDefend( creatures[i] ) )
            {
                smallest = creatures[i].getAttack() + creatures[i].getDefence();
                indexOfWeakest = i;
            }
        }

        creatures[indexOfWeakest].take();

        return;
    }

    // there is such creature - creature defends the player
    creatures[index].tap();
}
