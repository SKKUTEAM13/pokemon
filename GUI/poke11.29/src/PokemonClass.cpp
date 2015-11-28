#include <ctime>
#include <iostream>
#include "PokemonClass.h"

using namespace std;
///////////기본 포켓몬 클래스 함수 정의 

Pokemon::Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2)
	: vital(vital + level * 5), attack(attack + level), defense(defense + level), curExp(0), level(level)
{
	strcpy(this->name, name);
	strcpy(this->skillSeries[0], skillName1);
	strcpy(this->skillSeries[1], skillName2);
	addExp = 10 + 2 * level;
	limitExp = 10 * level;
}

void Pokemon::levelUp(int overExp) // 초과한 경험치
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
char * Pokemon::getSkill(int i) { return skillSeries[i - 1]; } // 포켓몬이 가지고 있는 i 번째 스킬 이름 반환. 
char * Pokemon::getName() { return name; }



////// 피카츄 클래스 함수 정의
Pikachu::Pikachu(int level) : Pokemon(70, 45, 35, 70, level, "피카츄", "백만 볼트", "몸통 박치기") { }

int Pikachu::FirstSkill(char skillName[])  // 첫번째 스킬 기본 데미지와 이름 반환
{
	srand(time(NULL));
	int variable = rand() % 15 - 5;
	strcpy(skillName, getSkill(1));
	int damage = getAttack() + variable;
	return damage;
}

int Pikachu::SecondSkill(char skillName[]) // 두번째 스킬 기본 데미지와 이름 반환
{
	srand(time(NULL));
	int variable = rand() % 10 - 3;
	strcpy(skillName, getSkill(2));
	int damage = getAttack() + variable;
	return damage;
}

///// 구구 클래스 함수 정의

GuGu::GuGu(int level) : Pokemon(60, 50, 30, 60, level, "구구", "바람일으키기", "전광석화") { }

int GuGu::FirstSkill(char skillName[])
{
	srand(time(NULL));
	int variable = rand() % 15 - 5;
	strcpy(skillName, getSkill(1));
	int damage = getAttack();
	return damage;
}

int GuGu::SecondSkill(char skillName[])
{
	srand(time(NULL));
	int variable = rand() % 10 - 3;
	strcpy(skillName, getSkill(2));
	int damage = getAttack() + 10;
	return damage;
}