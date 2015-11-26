#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdio>

#include "BattleHandler.h"
#include "PokemonClass.h"

using namespace std;


int main()
{
	srand(time(NULL));
	int random = rand() % 2;
	battleHandler a;
	GuGu g(1);
	Pikachu p(1), q(1);

	if (random)
		a.battleStart(&p, &g);
	else
		a.battleStart(&p, &q);
	return 0;

}