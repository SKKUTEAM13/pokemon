#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__

class Pokemon
{
private:
	int fullVital;				// �ִ� ü��
	int vital;					// ���� ü��
	int attack;					// ���ݷ�
	int defense;				// ����
	int level;
	int curExp;				    // ���� ����ġ
	int addExp;				    // �̰��� �� ����ġ ������
	int limitExp;				// ���� ���� ������ ����ġ �ʿ䷮;
	char name[20];
	char skillSeries[4][30] = { 0, };
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, char * name, char * skillName1, char * skillName2);
	virtual int FirstSkill(char skillName[]) = 0;
	virtual int SecondSkill(char skillName[]) = 0;
	void levelUp(int overExp);						// �ʰ��� ����ġ
	int damageCalc(int skill, int opDefense);		// ���� ���°� �Ӽ����� ����Ͽ� ���� ������ ������ ���
	void Damaged(int damage);
	void Heal();
	int getAttack();
	int getVital();
	int getDefense();
	int getFullVital();
	char * getSkill(int i); // ���ϸ��� ������ �ִ� i ��° ��ų �̸� ��ȯ. 
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