#include "BattleHandler.h"
#include <iostream>


// 배틀핸들러 클래스 정의
void battleHandler::playerTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum)
{
	int damage;
	char skillName[50];
	int attack;

	//cout << "Player's Turn!" << endl;
	//getchar();
	//cout << "어떻게 공격 할까? (1, 2) : ";
	//cin >> skillNum;

	switch (skillNum + 1)
	{
	case 1:
		attack = myPoke->FirstSkill(skillName);
		//getchar();
		break;

	case 2:
		attack = myPoke->SecondSkill(skillName);
		//	getchar();
		break;
	}

	//cout << myPoke->getName() << "의 " << skillName << "!" << endl;
	//getchar();

	damage = myPoke->damageCalc(attack, opPoke->getDefense());
	opPoke->Damaged(damage);

	//cout << "상대방의 " << opPoke->getName() << "는 " << damage << "의 데미지를 입었다." << endl;
	//cout << "상대방 " << opPoke->getName() << "의 체력 : " << opPoke->getVital() << "HP" << endl;
	//getchar();

}
void battleHandler::opponentTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum) {

	int damage;
	char skillName[50];
	int attack;

	//cout << "Opponent's Turn!" << endl;
	//getchar();

	switch (skillNum)
	{
	case 1:
		attack = opPoke->FirstSkill(skillName);
		break;
	case 2:
		attack = opPoke->SecondSkill(skillName);
		break;
	}
	//cout << opPoke->getName() << "의 " << skillName << "!" << endl;
	//getchar();
	damage = opPoke->damageCalc(attack, myPoke->getDefense());
	myPoke->Damaged(damage);
	//cout << "내 " << myPoke->getName() << "는 " << damage << "의 데미지를 입었다." << endl;
	//cout << "내 " << myPoke->getName() << "의 체력 : " << myPoke->getVital() << "HP" << endl;
	//getchar();

}
void battleHandler::battleStart(Pokemon * myPoke, Pokemon * opPoke)
{
	//cout << "야생의 " << opPoke->getName() << "가 나타났다!" << endl;
	//	getchar();
	//cout << "Player의 " << myPoke->getName() << "과 " << "Opponent의 " << opPoke->getName() << "의 대결!" << endl;
	//cout << "내 " << myPoke->getName() << "의 체력 : " << myPoke->getVital() << endl;
	//cout << "상대방 " << opPoke->getName() << "의 체력 : " << opPoke->getVital() << endl;

	//getchar();
	while (1)
	{
		playerTurn(myPoke, opPoke, 2);

		if (opPoke->getVital() == 0) {
			//	cout << "상대방의 " << opPoke->getName() << "가 쓰러졌다!" << endl;
			//	getchar();
			//	cout << "나의 승리!" << endl;
			//	getchar();
			break;
		}
		opponentTurn(myPoke, opPoke, 1);

		if (myPoke->getVital() == 0) {
			//		cout << "내 " << myPoke->getName() << "가 쓰러졌다!" << endl;
			//		getchar();
			//	cout << "나의 패배!" << endl;
			//	getchar();
			break;
		}
	}

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