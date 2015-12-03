#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__


class Pokemon
{
private:
	int fullVital;				// �ִ� ü��
	int vital;					// ���� ü��
	int attack;					// ���ݷ�
	int defense;				// ���� ���� �ۼ�Ʈ �ִ� 100%!!
	int level;
	int curExp;				    // ���� ����ġ
	int addExp;				    // �̰��� �� ����ġ ������
	int limitExp;				// ���� ���� ������ ����ġ �ʿ䷮;
	char name[20];
	char skillSeries[4][30] = { 0, };
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2);
	void levelUp(int overExp);						// �ʰ��� ����ġ
	int ExpUp(void);
	int isLevelUp();
	int damageCalc(int skill, int opDefense);		// ���� ���°� �Ӽ����� ����Ͽ� ���� ������ ������ ���
	void Damaged(int damage);
	void Heal();
	int getCurExp();
	int getLimitExp();
	int getLevel();
	int getAttack();
	int getVital();
	int getDefense();
	int getFullVital();
	char * getSkill(int i); // ���ϸ��� ������ �ִ� i ��° ��ų �̸� ��ȯ. 
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