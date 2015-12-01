#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__

using namespace std;
#include <string>

class Pokemon
{
private:
	int fullVital;				// 최대 체력
	int vital;					// 현재 체력
	int attack;					// 공격력
	int defense;				// 방어력
	int level;
	int curExp;				    // 현재 경험치
	int addExp;				    // 이겼을 때 경험치 증가량
	int limitExp;				// 현재 레벨 레벨업 경험치 필요량;
	string name;
	string skillSeries[4];
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, string name, string skillName1, string skillName2);
	virtual int FirstSkill(string skillName) = 0;
	virtual int SecondSkill(string skillName) = 0;
	void levelUp(int overExp);						// 초과한 경험치
	int damageCalc(int skill, int opDefense);		// 나의 방어력과 속성등을 고려하여 상대방 공격의 데미지 계산
	void Damaged(int damage);
	int getAttack();
	int getVital();
	int getDefense();
	string getSkill(int i); // 포켓몬이 가지고 있는 i 번째 스킬 이름 반환. 
	string getName();
};

class Pikachu : public Pokemon
{
public:
	Pikachu(int level);

	int FirstSkill(string skillName);
	int SecondSkill(string skillName);

};

class GuGu : public Pokemon
{
public:
	GuGu(int level);

	int FirstSkill(string skillName);
	int SecondSkill(string skillName);
};

#endif