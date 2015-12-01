#include <ctime>
#include <iostream>
#include "PokemonClass.h"
#include <string>

using namespace std;
///////////�⺻ ���ϸ� Ŭ���� �Լ� ���� 

Pokemon::Pokemon(int vital, int attack, int defense, int fullVital, int level, string name, string skillName1, string skillName2)
	: vital(vital + level * 5), attack(attack + level), defense(defense + level), curExp(0), level(level)
{
	this->name = name;
	this->skillSeries[0] = skillName1;
	this->skillSeries[1] = skillName2;
	addExp = 10 + 2 * level;
	limitExp = 10 * level;
}

void Pokemon::levelUp(int overExp) // �ʰ��� ����ġ
{
	level++;
	defense++;
	vital = fullVital + level * 5;
	attack += (2 * level);
	curExp = overExp;
	addExp = 10 + 2 * level;
	limitExp = 10 * level;
}

int Pokemon::damageCalc(int skill, int opDefense) {
	srand(time(NULL));
	int realDamage = skill + (rand() % 5) - opDefense;
	if (realDamage <= 0)
		realDamage = 1;
	return realDamage;
}

void Pokemon::Damaged(int damage) {
	vital -= damage;
	if (vital < 0)
		vital = 0;
}
int Pokemon::getAttack() { return attack; }
int Pokemon::getVital() { return vital; }
int Pokemon::getDefense() { return defense; }
string Pokemon::getSkill(int i) { return skillSeries[i - 1]; } // ���ϸ��� ������ �ִ� i ��° ��ų �̸� ��ȯ. 
string Pokemon::getName() { return name; }



////// ��ī�� Ŭ���� �Լ� ����
Pikachu::Pikachu(int level) : Pokemon(70, 45, 35, 70, level, "��ī��", "�鸸 ��Ʈ", "���� ��ġ��") { }

int Pikachu::FirstSkill(string skillName)  // ù��° ��ų �⺻ �������� �̸� ��ȯ
{
	srand(time(NULL));
	int variable = rand() % 15 - 5;
	skillName = getSkill(1);
	int damage = getAttack() + variable;
	return damage;
}

int Pikachu::SecondSkill(string skillName) // �ι�° ��ų �⺻ �������� �̸� ��ȯ
{
	srand(time(NULL));
	int variable = rand() % 10 - 3;
	skillName = getSkill(2);
	int damage = getAttack() + variable;
	return damage;
}

///// ���� Ŭ���� �Լ� ����

GuGu::GuGu(int level) : Pokemon(60, 50, 30, 60, level, "����", "�ٶ�����Ű��", "������ȭ") { }

int GuGu::FirstSkill(string skillName)
{
	srand(time(NULL));
	int variable = rand() % 15 - 5;
	skillName = getSkill(1);
	int damage = getAttack();
	return damage;
}

int GuGu::SecondSkill(string skillName)
{
	srand(time(NULL));
	int variable = rand() % 10 - 3;
	skillName = getSkill(2);
	int damage = getAttack() + 10;
	return damage;
}
