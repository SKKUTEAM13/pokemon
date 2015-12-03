#include "BattleHandler.h"

// 배틀핸들러 클래스 정의
void battleHandler::playerTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum)
{
	int damage;
	char skillName[50];
	int attack;
	switch (skillNum + 1)
	{
	case 1:
		attack = myPoke->FirstSkill(skillName);
		break;

	case 2:
		attack = myPoke->SecondSkill(skillName);
		break;
	}

	damage = myPoke->damageCalc(attack, opPoke->getDefense());
	opPoke->Damaged(damage);

}
void battleHandler::opponentTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum) {

	int damage;
	char skillName[50];
	int attack;

	switch (skillNum)
	{
	case 1:
		attack = opPoke->FirstSkill(skillName);
		break;
	case 2:
		attack = opPoke->SecondSkill(skillName);
		break;
	}

	damage = opPoke->damageCalc(attack, myPoke->getDefense());
	myPoke->Damaged(damage);


}

Pokemon * battleHandler::selectPoke(int level, int selection) { // 레벨과 어떤 포켓몬을 받을것인지
	Pokemon * opPoke;
	switch (selection)
	{
	case GUGU:
		opPoke = new GuGu(level);
		break;
	case ABOKE:
		opPoke = new Aboke(level);
		break;
	case NYAONG:
		opPoke = new NyaongE(level);
		break;
	case DDOGAS:
		opPoke = new Ddogas(level);
		break;
	case JILPEOK:
		opPoke = new JilpeokE(level);
		break;
	case COIL:
		opPoke = new Coil(level);
		break;
	case DIGDA:
		opPoke = new Digda(level);
		break;
	case TANGURI:
		opPoke = new Tanguri(level);
		break;
	case PHANTOM:
		opPoke = new Phantom(level);
		break;
	case YUNGELA:
		opPoke = new Yungela(level);
		break;
	case PARASECT:
		opPoke = new Parasect(level);
		break;
	case DANDANGI:
		opPoke = new Dandangi(level);
		break;
	case MAJAYONG:
		opPoke = new Majayong(level);
		break;
	case DDODOGAS:
		opPoke = new Ddodogas(level);
		break;
	case DACTRIO:
		opPoke = new Dactrio(level);
		break;
	case YADON:
		opPoke = new Yadon(level);
		break;
	case YADORAN:
		opPoke = new Yadoran(level);
		break;
	default:
		opPoke = new GuGu(1);
		break;

	}

	return opPoke;
}