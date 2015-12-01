#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__

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
	char name[20];
	char skillSeries[4][30] = { 0, };
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2);
	virtual int FirstSkill(char skillName[]) = 0;
	virtual int SecondSkill(char skillName[]) = 0;
	void levelUp(int overExp);						// 초과한 경험치
	int damageCalc(int skill, int opDefense);		// 나의 방어력과 속성등을 고려하여 상대방 공격의 데미지 계산
	void Damaged(int damage);
	void Heal();
	int getAttack();
	int getVital();
	int getDefense();
	int getFullVital();
	char * getSkill(int i); // 포켓몬이 가지고 있는 i 번째 스킬 이름 반환. 
	char * getName();
};

class Pikachu : public Pokemon
{
public:
	Pikachu(int level);

	int FirstSkill(char skillName[]);
	int SecondSkill(char skillName[]);

};

class GuGu : public Pokemon
{
public:
	GuGu(int level);

	int FirstSkill(char skillName[]);
	int SecondSkill(char skillName[]);
};

#endif