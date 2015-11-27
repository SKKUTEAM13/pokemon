#pragma once

#define VERTICLE_LINE 14
#define HORIZONTAL_LINE 10

/*
*	0 : 장애물 1 : 길 2 : 풀 
*
*/

class map
{
private:
	int map_array[VERTICLE_LINE + 1][HORIZONTAL_LINE + 1];
public:
	int map_number;			// 현재 맵 번호
	int num_npc;

	void Init();
	int Link_Map(int *x, int *y);
	void Loading_Map(int *Map_DB);
	int Check_Map(int x, int y);
	int GetNum(int x, int y);
};