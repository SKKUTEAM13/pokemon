#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__


class Pokemon
{
private:
	int fullVital;				// 최대 체력
	int vital;					// 현재 체력
	int attack;					// 공격력
	int defense;				// 방어력 기준 퍼센트 최대 100%!!
	int level;
	int curExp;				    // 현재 경험치
	int addExp;				    // 이겼을 때 경험치 증가량
	int limitExp;				// 현재 레벨 레벨업 경험치 필요량;
	char name[20];
	char skillSeries[4][30] = { 0, };
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2);
	void levelUp(int overExp);						// 초과한 경험치
	int ExpUp(void);
	int isLevelUp();
	int damageCalc(int skill, int opDefense);		// 나의 방어력과 속성등을 고려하여 상대방 공격의 데미지 계산
	void Damaged(int damage);
	void Heal();
	int getCurExp();
	int getLimitExp();
	int getLevel();
	int getAttack();
	int getVital();
	int getDefense();
	int getFullVital();
	char * getSkill(int i); // 포켓몬이 가지고 있는 i 번째 스킬 이름 반환. 
	char * getName();
	int getAddExp(void);


	int FirstSkill(char skillName[]);
	int SecondSkill(char skillName[]);
};

class Pikachu : public Pokemon
{
public:
	Pikachu(int level);
};

class GuGu : public Pokemon
{
public:
	GuGu(int level);
};

class Aboke : public Pokemon
{
public:
	Aboke(int level);
};

class NyaongE : public Pokemon
{
public:
	NyaongE(int level);
};

class Ddogas: public Pokemon
{
public:
	Ddogas(int level);
};

class JilpeokE : public Pokemon
{
public:
	JilpeokE(int level);
};

class Coil : public Pokemon
{
public:
	Coil(int level);
};

class Digda : public Pokemon
{
public:
	Digda(int level);

};

class Tanguri : public Pokemon
{
public:
	Tanguri(int level);
};


class Phantom : public Pokemon
{
public:
	Phantom(int level);
};

class Yungela : public Pokemon
{
public:
	Yungela(int level);
};

class Parasect : public Pokemon
{
public:
	Parasect(int level);
};

class Dandangi : public Pokemon
{
public:
	Dandangi(int level);
};

class Majayong : public Pokemon
{
public:
	Majayong(int level);
};

class Ddodogas : public Pokemon
{
public:
	Ddodogas(int level);
};

class Dactrio : public Pokemon
{
public:
	Dactrio(int level);

};


class Yadon : public Pokemon
{
public:
	Yadon(int level);
};

class Yadoran : public Pokemon
{
public:
	Yadoran(int level);
};



#endif