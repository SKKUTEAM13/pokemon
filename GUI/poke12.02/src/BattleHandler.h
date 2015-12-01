#ifndef __BATTLEHANDLER_H__
#define __BATTLEHANDLER_H__

#include "PokemonClass.h"

class battleHandler
{
public:
	void playerTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum);
	void opponentTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum);
	void battleStart(Pokemon * myPoke, Pokemon * opPoke);
};

#endif