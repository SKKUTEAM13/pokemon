#pragma once

#include "object.h"

#define VERTICLE_LINE 14
#define HORIZONTAL_LINE 10
#define MAX_NPC 2
/*
*	0 : ��ֹ� 1 : �� 2 : Ǯ 3 : ���� 4 : �̲��� 5 : NPC
*	���� = �ʹ�ȣ/x��ǥ 2�ڸ�/y��ǥ 2�ڸ�/3
*	NPC	 = �̹�����ȣ/���� ����(0~3)/5
*/

class map
{
private:
	int map_array[VERTICLE_LINE + 1][HORIZONTAL_LINE + 1];
public:
	bool IsMap;
	int map_number;			// ���� �� ��ȣ
	int num_npc;
	people NPC[MAX_NPC];

	void Init();
	int Link_Map(int *x, int *y);
	void Loading_Map(int *Map_DB);
	int Check_Map(int x, int y);
	int GetNum(int x, int y);
	void InitNPC(int input, int x, int y, int loop);
	void DeleteNPC();
};