#include "creature.h"
#include "stdlib.h"
#include "cmath"
#include <iostream>
#include <cstring>

using namespace std;

Creature::Creature()
{
    attack = rand() % 4 + 1;
    defence = rand() % 4 + 1;
    unsigned int totalCost = getTotalCost();

    memset( cost, 0, 5 * sizeof( unsigned int ) );

    for ( unsigned int i = 0; i < totalCost; i++ )
    {
        switch ( rand() % 5 )
        {
            case 0: cost[C_WHITE]++; break;
            case 1: cost[C_BLUE]++; break;
            case 2: cost[C_BLACK]++; break;
            case 3: cost[C_RED]++; break;
            case 4: cost[C_GREEN]++; break;
        }
    }

    summoningSickness = false;
}

void Creature::summon()
{
    if ( isPlayed() )
    {
        cerr << "Creature has already been played." << endl;
        return;
    }

    summoningSickness = true;
    play();
}

void Creature::prepare()
{
    summoningSickness = false;
}

bool Creature::justSummoned() const
{
    return summoningSickness;
}

unsigned int Creature::getAttack() const
{
    return attack;
}

unsigned int Creature::getDefence() const
{
    return defence;
}

unsigned int Creature::getTotalCost() const
{
    return ( unsigned int ) round( ( attack + defence ) / 2.0 );
}

unsigned int Creature::getSpecialCost( const mana manaColor ) const
{
    switch ( manaColor )
    {
        case BLACK: return cost[C_BLACK];
        case WHITE: return cost[C_WHITE];
        case BLUE: return cost[C_BLUE];
        case RED: return cost[C_RED];
        case GREEN: return cost[C_GREEN];
        default: return 0;
    }
}
