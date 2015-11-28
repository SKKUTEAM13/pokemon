#include "BattleHandler.h"
#include <iostream>

using namespace std;

// ��Ʋ�ڵ鷯 Ŭ���� ����
void battleHandler::playerTurn(Pokemon * myPoke, Pokemon * opPoke)
{
	int damage;
	char skillName[50];
	int skillNum;
	int attack;

	cout << "Player's Turn!" << endl;
	getchar();
	cout << "��� ���� �ұ�? (1, 2) : ";
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

	cout << myPoke->getName() << "�� " << skillName << "!" << endl;
	getchar();

	damage = myPoke->damageCalc(attack, opPoke->getDefense());
	opPoke->Damaged(damage);

	cout << "������ " << opPoke->getName() << "�� " << damage << "�� �������� �Ծ���." << endl;
	cout << "���� " << opPoke->getName() << "�� ü�� : " << opPoke->getVital() << "HP" << endl;
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
	cout << opPoke->getName() << "�� " << skillName << "!" << endl;
	getchar();
	damage = opPoke->damageCalc(attack, myPoke->getDefense());
	myPoke->Damaged(damage);
	cout << "�� " << myPoke->getName() << "�� " << damage << "�� �������� �Ծ���." << endl;
	cout << "�� " << myPoke->getName() << "�� ü�� : " << myPoke->getVital() << "HP" << endl;
	getchar();

}
void battleHandler::battleStart(Pokemon * myPoke, Pokemon * opPoke)
{
	cout << "�߻��� " << opPoke->getName() << "�� ��Ÿ����!" << endl;
	getchar();
	cout << "Player�� " << myPoke->getName() << "�� " << "Opponent�� " << opPoke->getName() << "�� ���!" << endl;
	cout << "�� " << myPoke->getName() << "�� ü�� : " << myPoke->getVital() << endl;
	cout << "���� " << opPoke->getName() << "�� ü�� : " << opPoke->getVital() << endl;

	getchar();
	while (1)
	{
		playerTurn(myPoke, opPoke);

		if (opPoke->getVital() == 0) {
			cout << "������ " << opPoke->getName() << "�� ��������!" << endl;
			getchar();
			cout << "���� �¸�!" << endl;
			getchar();
			break;
		}
		opponentTurn(myPoke, opPoke);

		if (myPoke->getVital() == 0) {
			cout << "�� " << myPoke->getName() << "�� ��������!" << endl;
			getchar();
			cout << "���� �й�!" << endl;
			getchar();
			break;
		}
	}

}