#include "BattleHandler.h"
#include <iostream>

using namespace std;

// 배틀핸들러 클래스 정의
void battleHandler::playerTurn(Pokemon * myPoke, Pokemon * opPoke)
{
	int damage;
	char skillName[50];
	int skillNum;
	int attack;

	cout << "Player's Turn!" << endl;
	getchar();
	cout << "어떻게 공격 할까? (1, 2) : ";
	cin >> skillNum;

	switch (skillNum)
	{
	case 1:
		attack = myPoke->FirstSkill(skillName);
		getchar();
		break;

	case 2:
		attack = myPoke->SecondSkill(skillName);
		getchar();
		break;
	}

	cout << myPoke->getName() << "의 " << skillName << "!" << endl;
	getchar();

	damage = myPoke->damageCalc(attack, opPoke->getDefense());
	opPoke->Damaged(damage);

	cout << "상대방의 " << opPoke->getName() << "는 " << damage << "의 데미지를 입었다." << endl;
	cout << "상대방 " << opPoke->getName() << "의 체력 : " << opPoke->getVital() << "HP" << endl;
	getchar();

}
void battleHandler::opponentTurn(Pokemon * myPoke, Pokemon * opPoke) {

	int damage;
	char skillName[50];
	int skillNum;
	int attack;

	cout << "Opponent's Turn!" << endl;
	getchar();
	skillNum = (rand() % 2) + 1;

	switch (skillNum)
	{
	case 1:
		attack = opPoke->FirstSkill(skillName);
		break;
	case 2:
		attack = opPoke->SecondSkill(skillName);
		break;
	}
	cout << opPoke->getName() << "의 " << skillName << "!" << endl;
	getchar();
	damage = opPoke->damageCalc(attack, myPoke->getDefense());
	myPoke->Damaged(damage);
	cout << "내 " << myPoke->getName() << "는 " << damage << "의 데미지를 입었다." << endl;
	cout << "내 " << myPoke->getName() << "의 체력 : " << myPoke->getVital() << "HP" << endl;
	getchar();

}
void battleHandler::battleStart(Pokemon * myPoke, Pokemon * opPoke)
{
	cout << "야생의 " << opPoke->getName() << "가 나타났다!" << endl;
	getchar();
	cout << "Player의 " << myPoke->getName() << "과 " << "Opponent의 " << opPoke->getName() << "의 대결!" << endl;
	cout << "내 " << myPoke->getName() << "의 체력 : " << myPoke->getVital() << endl;
	cout << "상대방 " << opPoke->getName() << "의 체력 : " << opPoke->getVital() << endl;

	getchar();
	while (1)
	{
		playerTurn(myPoke, opPoke);

		if (opPoke->getVital() == 0) {
			cout << "상대방의 " << opPoke->getName() << "가 쓰러졌다!" << endl;
			getchar();
			cout << "나의 승리!" << endl;
			getchar();
			break;
		}
		opponentTurn(myPoke, opPoke);

		if (myPoke->getVital() == 0) {
			cout << "내 " << myPoke->getName() << "가 쓰러졌다!" << endl;
			getchar();
			cout << "나의 패배!" << endl;
			getchar();
			break;
		}
	}

}