#include <iostream>
#include "matrix.h"
#include "parser.h"
#include <map>
#include <vector>

using namespace std;

int main()
{
    Parser p;
    p.queueFile("a.txt");
    p.process();
    ParserRawTopology prt = p.getMapping();
    /*for (map<int, vector<int> >::iterator it = prt.begin();
         it != prt.end(); it++)
    {
        cout << it->first << " ";
        for (unsigned int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i] << " ";
        }
        cout << endl;
    }*/

    return 0;
}

