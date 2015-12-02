#include <ctime>
#include <iostream>
#include "PokemonClass.h"

using namespace std;
///////////기본 포켓몬 클래스 함수 정의 

Pokemon::Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2)
	: vital(vital + level * 5), attack(attack + level), fullVital(vital + level * 5), defense(defense + level), curExp(0), level(level)
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

char * Pokemon::getSkill(int i) { return skillSeries[i - 1]; } // 포켓몬이 가지고 있는 i 번째 스킬 이름 반환. 
char * Pokemon::getName() { return name; }


int Pokemon::FirstSkill(char skillName[])  // 첫번째 스킬 기본 데미지와 이름 반환
{
	srand(time(NULL));
	int variable = rand() % 15 - 5;
	strcpy(skillName, getSkill(1));
	int damage = getAttack() + variable;
	return damage;
}


int Pokemon::SecondSkill(char skillName[]) // 두번째 스킬 기본 데미지와 이름 반환
{
	srand(time(NULL));
	int variable = rand() % 10 - 3;
	strcpy(skillName, getSkill(2));
	int damage = getAttack() + variable;
	return damage;
}

////// 피카츄 클래스 함수 정의
Pikachu::Pikachu(int level) : Pokemon(70, 45, 35, 70, level, "pikachu", "Thunder bolt", "Iron Tail") { }


///// 구구 클래스 함수 정의
GuGu::GuGu(int level) : Pokemon(60, 50, 30, 60, level, "Arboke", "Bite", "First attack") { }


Aboke::Aboke(int level) : Pokemon(70, 50, 20, 70, level, "Arboke", "Poison Bite", "Poison Tail") { }

NyaongE::NyaongE(int level) : Pokemon(45, 55, 25, 45, level, "Naong", "Cat Money", "Claw") { }


Ddogas::Ddogas(int level) : Pokemon(70, 50, 30, 70, level, "Ddogas", "Poison Gas", "Poison Dust") { }

Ddodogas::Ddodogas(int level) : Pokemon(110, 60, 40, 110, level, "Ddodogas", "Venom", "Smog") { }

JilpeokE::JilpeokE(int level) : Pokemon(90, 35, 30, 90, level, "JilpeokE", "Sewage Wave", "Belch") { }


Coil::Coil(int level) : Pokemon(45, 50, 25, 45, level, "Coil", "Wild Volt", "Spark") { }


Digda::Digda(int level) : Pokemon(50, 40, 35, 50, level, "Digda", "Dig Hole", "Mud Attack") { }

Dactrio::Dactrio(int level) : Pokemon(70, 55, 40, 70, level, "Dactrio", "Earth Quake", "Sand Hole") { }

Tanguri::Tanguri(int level) : Pokemon(60, 55, 25, 60, level, "Tanguri", "Bone Rush", "Bone Boomerang") { }


Phantom::Phantom(int level) : Pokemon(80, 80, 20, 80, level, "Phantom", "Nightmare", "Shadow Punch") { }


Yungela::Yungela(int level) : Pokemon(60, 70, 35, 60, level, "Yungela", "Psychic", "Psycho Cutter") { }


Parasect::Parasect(int level) : Pokemon(70, 50, 30, 70, level, "Parasect", "Mushroom Spore", "Leaf Attack") { }


Dandangi::Dandangi(int level) : Pokemon(40, 30, 55, 40, level, "Dandangi", "Bite", "Slap") { }


Majayong::Majayong(int level) : Pokemon(60, 40, 40, 60, level, "Majayong", "Counter", "Mirror Coat") { }



Yadon::Yadon(int level) : Pokemon(60, 30, 30, 60, level, "Yadon", "Water Beam", "Aqua Tail") { }

Yadoran::Yadoran(int level) : Pokemon(80, 60, 40, 80, level, "Yadoran", "Shell Attack", "Hydropump") { }



