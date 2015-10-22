#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <piecelocation.h>
#include <gamestate.h>

using namespace std;

class bishop
{
public:
    bishop();


    vector <pieceLocation> getMoves (gameState game);
    void moveTo(pieceLocation moveLoc);
    string toString();


};

#endif // BISHOP_H
