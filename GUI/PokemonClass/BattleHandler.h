#ifndef __BATTLEHANDLER_H__
#define __BATTLEHANDLER_H__



enum { GUGU = 1, ABOKE, NYAONG, DDOGAS, JILPEOK, COIL, DIGDA, TANGURI, PHANTOM, YUNGELA, PARASECT, DANDANGI, MAJAYONG, DDODOGAS, DACTRIO, YADON, YADORAN };

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