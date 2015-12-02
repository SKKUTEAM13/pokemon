#include "BattleHandler.h"
#include <iostream>


// ��Ʋ�ڵ鷯 Ŭ���� ����
void battleHandler::playerTurn(Pokemon * myPoke, Pokemon * opPoke, int skillNum)
{
	int damage;
	char skillName[50];
	int attack;

	//cout << "Player's Turn!" << endl;
	//getchar();
	//cout << "��� ���� �ұ�? (1, 2) : ";
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

	//cout << myPoke->getName() << "�� " << skillName << "!" << endl;
	//getchar();

	damage = myPoke->damageCalc(attack, opPoke->getDefense());
	opPoke->Damaged(damage);

	//cout << "������ " << opPoke->getName() << "�� " << damage << "�� �������� �Ծ���." << endl;
	//cout << "���� " << opPoke->getName() << "�� ü�� : " << opPoke->getVital() << "HP" << endl;
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
	//cout << opPoke->getName() << "�� " << skillName << "!" << endl;
	//getchar();
	damage = opPoke->damageCalc(attack, myPoke->getDefense());
	myPoke->Damaged(damage);
	//cout << "�� " << myPoke->getName() << "�� " << damage << "�� �������� �Ծ���." << endl;
	//cout << "�� " << myPoke->getName() << "�� ü�� : " << myPoke->getVital() << "HP" << endl;
	//getchar();

}
void battleHandler::battleStart(Pokemon * myPoke, Pokemon * opPoke)
{
	//cout << "�߻��� " << opPoke->getName() << "�� ��Ÿ����!" << endl;
	//	getchar();
	//cout << "Player�� " << myPoke->getName() << "�� " << "Opponent�� " << opPoke->getName() << "�� ���!" << endl;
	//cout << "�� " << myPoke->getName() << "�� ü�� : " << myPoke->getVital() << endl;
	//cout << "���� " << opPoke->getName() << "�� ü�� : " << opPoke->getVital() << endl;

	//getchar();
	while (1)
	{
		playerTurn(myPoke, opPoke, 2);

		if (opPoke->getVital() == 0) {
			//	cout << "������ " << opPoke->getName() << "�� ��������!" << endl;
			//	getchar();
			//	cout << "���� �¸�!" << endl;
			//	getchar();
			break;
		}
		opponentTurn(myPoke, opPoke, 1);

		if (myPoke->getVital() == 0) {
			//		cout << "�� " << myPoke->getName() << "�� ��������!" << endl;
			//		getchar();
			//	cout << "���� �й�!" << endl;
			//	getchar();
			break;
		}
	}

}

Pokemon * battleHandler::selectPoke(int level, int selection) { // ������ � ���ϸ��� ����������
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
	}

	return opPoke;
}