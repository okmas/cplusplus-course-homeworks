#include "land.h"
#include "card.h"
#include "stdlib.h"
#include <iostream>

using namespace std;

Land::Land()
{
    switch ( rand() % 5 )
    {
        case 0: type = PLAINS; break;
        case 1: type = ISLAND; break;
        case 2: type = SWAMP; break;
        case 3: type = MOUNTAIN; break;
        case 4: type = FOREST; break;
    }
}

landType Land::getType() const
{
    return type;
}

mana Land::getMana()
{
    if ( ! isPlayed() )
    {
        cerr << "Card needs to be on the table to produce mana." << endl;
        return NONE;
    }

    if ( isTapped() )
    {
        return NONE;
    }

    tap();

    switch ( getType() )
    {
        case PLAINS: return WHITE;
        case ISLAND: return BLUE;
        case SWAMP: return BLACK;
        case MOUNTAIN: return RED;
        case FOREST: return GREEN;
        default: return NONE;
    }
}
