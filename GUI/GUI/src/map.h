#pragma once

#define VERTICLE_LINE 14
#define HORIZONTAL_LINE 10

/*
*	0 : ��ֹ� 1 : �� 2 : Ǯ 
*
*/

class map
{
private:
	int map_array[VERTICLE_LINE + 1][HORIZONTAL_LINE + 1];
public:
	int map_number;			// ���� �� ��ȣ
	int num_npc;

	void Init();
	int Link_Map(int *x, int *y);
	void Loading_Map(int *Map_DB);
	int Check_Map(int x, int y);
	int GetNum(int x, int y);
};