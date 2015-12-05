#ifndef __BATTLEHANDLER_H__
#define __BATTLEHANDLER_H__



enum { GUGU = 1, DIGDA, ABOKE, YADON, TANGURI, COIL, PARASECT, DACTRIO, DDOGAS,  NYAONG, JILPEOK, YUNGELA, DANDANGI, MAJAYONG, DDODOGAS, YADORAN, PHANTOM
};

#include "PokemonClass.h"

class battleHandler
{
public:
	void playerTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum);
	void opponentTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum);
	void battleStart(Pokemon * myPoke, Pokemon * opPoke);
	Pokemon * selectPoke(int level, int selection);
};

#endif