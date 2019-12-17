#include <iostream>
#include <ctime>
#include <cstdlib>
#include "player.h"
using namespace std;
int main(int argc, char **argv
         )
{
    if (argc > 1) srand(atoi(argv[1]));
    else srand(time(NULL));

    char name1[30];
    char name2[30];
    cout << "MAGIC THE GATHERING SIMULATION" << endl << endl;
    cout << "First player name: ";
    cin.getline(name1,30);
    cout << "Second player name: ";
    cin.getline(name2,30);
    cout << endl << endl;
    Player player1(name1);
    Player player2(name2);
    player1.printInfo();
    player2.printInfo();
    unsigned int round = 0;
    cout << endl << endl << "Let the game begin." << endl << endl;
    bool whoIsFirst = (rand() % 2 == 0);
    cin.get();
    while(player1.getLife()>0 && player2.getLife()>0)
    {
        round++;
        cout << "ROUND " << round << ".: " << endl;
        if(whoIsFirst)
        {
            player1.oneTurn(player2);
            player1.printInfo();
            if(player2.getLife()>0) player2.oneTurn(player1);
            player2.printInfo();
        }
        else
        {
            player2.oneTurn(player1);
            player2.printInfo();
            if(player1.getLife()>0)  player1.oneTurn(player2);
            player1.printInfo();
        }
        cin.get();
        if(round>60)
        {
            cout << "Noone wins, probably draw. " << endl;
            return 0;
        }
    }
    if(player1.getLife()>0)
    {
        cout << player1.getName() << " won!" << endl;
    }
    else
    {
        cout << player2.getName() << " won!" << endl;
    }
    cin.get();
    return 0;
}
