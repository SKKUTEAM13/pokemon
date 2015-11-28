#ifndef __BATTLEHANDLER_H__
#define __BATTLEHANDLER_H__

#include "PokemonClass.h"

class battleHandler
{
public:
	void playerTurn(Pokemon * myPoke, Pokemon * opPoke);
	void opponentTurn(Pokemon * myPoke, Pokemon * opPoke);
	void battleStart(Pokemon * myPoke, Pokemon * opPoke);
};

#endif