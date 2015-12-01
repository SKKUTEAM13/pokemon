#ifndef __POKEMONCLASS_H__
#define __POKEMONCLASS_H__

using namespace std;
#include <string>

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
	string name;
	string skillSeries[4];
public:
	Pokemon(int vital, int attack, int defense, int fullVital, int level, string name, string skillName1, string skillName2);
	virtual int FirstSkill(string skillName) = 0;
	virtual int SecondSkill(string skillName) = 0;
	void levelUp(int overExp);						// �ʰ��� ����ġ
	int damageCalc(int skill, int opDefense);		// ���� ���°� �Ӽ����� ����Ͽ� ���� ������ ������ ���
	void Damaged(int damage);
	int getAttack();
	int getVital();
	int getDefense();
	string getSkill(int i); // ���ϸ��� ������ �ִ� i ��° ��ų �̸� ��ȯ. 
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