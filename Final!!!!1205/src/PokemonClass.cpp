#include <ctime>
#include <iostream>
#include "PokemonClass.h"

using namespace std;
///////////�⺻ ���ϸ� Ŭ���� �Լ� ���� 

Pokemon::Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2)
	: vital(vital + level * 3), attack(attack * (20+level)/20), fullVital(vital + level * 3), defense((level+50)*defense/50), curExp(0), level(level)
{
	strcpy(this->name, name);
	strcpy(this->skillSeries[0], skillName1);
	strcpy(this->skillSeries[1], skillName2);
	addExp = 10 + 2 * level;
	limitExp = 10 * level;
}

int Pokemon::isLevelUp() { // ����ġ�� �������Ҷ��� �糪?
	if (curExp >= limitExp)
		return 1;
	else
		return 0;
}

int Pokemon::ExpUp(int opLevel) { // ���� �¸� �� ����ġ ����
	int add;
	add = (addExp - 3*(level - opLevel)); //�� ������ �� ������ ���� ���ϱ� 3�� ����ġ �г�Ƽ
	if (add <= 0)
		add = 1;
	curExp += add;
	if (isLevelUp())
		levelUp(curExp - limitExp); // �ʰ��� ����ġ�� �Ѱ���.

	return addExp;
}

void Pokemon::levelUp(int overExp) // ������! (overExp : �ʰ��� ����ġ)
{
	level++;
	if (defense < 90)
		defense += 3;
	fullVital += (level / 2);
	vital = fullVital;
	attack = 11* attack / 10;
	curExp = overExp;
	addExp = 10 + 2 * level;
	limitExp = 10 * level;
}

int Pokemon::damageCalc(int skill, int opDefense) {
	srand(time(NULL));
	int realDamage = skill * (100 - opDefense) / 100;
	if (realDamage <= 0) 
		realDamage = 1;
	return realDamage;
}

void Pokemon::Damaged(int damage) {
	vital -= damage;
	if (vital < 0)
		vital = 0;
}
void Pokemon::Heal() {
	vital = fullVital;
}

int Pokemon::getCurExp() { return curExp; }
int Pokemon::getLimitExp() { return limitExp; }
int Pokemon::getLevel() { return level; }
int Pokemon::getAttack() { return attack; }
int Pokemon::getVital() { return vital; }
int Pokemon::getDefense() { return defense; }
int Pokemon::getFullVital() { return fullVital; }
int Pokemon::getAddExp() { return addExp; }

char * Pokemon::getSkill(int i) { return skillSeries[i - 1]; } // ���ϸ��� ������ �ִ� i ��° ��ų �̸� ��ȯ. 
char * Pokemon::getName() { return name; }


int Pokemon::FirstSkill(char skillName[])  // ù��° ��ų �⺻ �������� �̸� ��ȯ
{
	srand(time(NULL));
	int variable = rand() % 6 - 4;
	strcpy(skillName, getSkill(1));
	int damage = getAttack() + variable;
	return damage;
}


int Pokemon::SecondSkill(char skillName[]) // �ι�° ��ų �⺻ �������� �̸� ��ȯ
{
	srand(time(NULL));
	strcpy(skillName, getSkill(2));
	int damage = getAttack();
	return damage;
}

////// ��ī�� Ŭ���� �Լ� ����
Pikachu::Pikachu(int level) : Pokemon(60, 30, 35, 60, level, "Pikachu", "Thunder bolt", "Iron Tail") { }


///// ���� Ŭ���� �Լ� ����
GuGu::GuGu(int level) : Pokemon(45, 10, 30, 45, level, "GuGu", "Sky Slam", "Wind Attack") { }


Aboke::Aboke(int level) : Pokemon(60, 30, 20, 60, level, "Arboke", "Poison Bite", "Poison Tail") { }

NyaongE::NyaongE(int level) : Pokemon(45, 20, 20, 45, level, "Naong", "Cat Money", "Claw") { }


Ddogas::Ddogas(int level) : Pokemon(70, 20, 30, 70, level, "Ddogas", "Poison Gas", "Poison Dust") { }

Ddodogas::Ddodogas(int level) : Pokemon(100, 20, 30, 100, level, "Ddodogas", "Venom", "Smog") { }

JilpeokE::JilpeokE(int level) : Pokemon(85, 25, 40, 85, level, "JilpeokE", "Sewage Wave", "Belch") { }


Coil::Coil(int level) : Pokemon(45, 30, 25, 45, level, "Coil", "Wild Volt", "Spark") { }


Digda::Digda(int level) : Pokemon(50, 15, 20, 50, level, "Digda", "Dig Hole", "Mud Attack") { }

Dactrio::Dactrio(int level) : Pokemon(70, 35, 25, 70, level, "Dactrio", "Earth Quake", "Sand Hole") { }

Tanguri::Tanguri(int level) : Pokemon(60, 20, 20, 60, level, "Tanguri", "Bone Rush", "Bone Boomerang") { }


Phantom::Phantom(int level) : Pokemon(80, 60, 30, 80, level, "Phantom", "Nightmare", "Shadow Punch") { }


Yungela::Yungela(int level) : Pokemon(70, 50, 20, 70, level, "Yungela", "Psychic", "Psycho Cutter") { }


Parasect::Parasect(int level) : Pokemon(70, 30, 30, 70, level, "Parasect", "Mushroom Spore", "Leaf Attack") { }


Dandangi::Dandangi(int level) : Pokemon(30, 15, 70, 30, level, "Dandangi", "Bite", "Slap") { }


Majayong::Majayong(int level) : Pokemon(60, 20, 50, 60, level, "Majayong", "Counter", "Mirror Coat") { }



Yadon::Yadon(int level) : Pokemon(60, 20, 30, 60, level, "Yadon", "Water Beam", "Aqua Tail") { }

Yadoran::Yadoran(int level) : Pokemon(80, 25, 45, 80, level, "Yadoran", "Shell Attack", "Hydropump") { }



