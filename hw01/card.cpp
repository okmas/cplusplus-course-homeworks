#include "card.h"
#include <iostream>

using namespace std;

Card::Card()
{
    tapped = false;
    table = false;
}

void Card::play()
{
    if ( isPlayed() )
    {
        cerr << "Card has already been played." << endl;
        return;
    }

    table = true;
    tapped = false;
}

void Card::take()
{
    if ( ! isPlayed() )
    {
        cerr << "Card isn't on the table." << endl;
        return;
    }

    table = false;
}

bool Card::isPlayed() const
{
    return table;
}

void Card::tap()
{
    if ( isTapped() )
    {
        cerr << "Card is already tapped." << endl;
        return;
    }

    tapped = true;
}

void Card::unTap()
{
    if ( ! isTapped() )
    {
        cerr << "Card is already untapped." << endl;
        return;
    }

    tapped = false;
}

bool Card::isTapped() const
{
    return tapped;
}
