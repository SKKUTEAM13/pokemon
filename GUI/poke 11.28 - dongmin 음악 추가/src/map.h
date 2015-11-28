#pragma once

#include "object.h"

#define VERTICLE_LINE 14
#define HORIZONTAL_LINE 10
#define MAX_NPC 2
/*
*	0 : 장애물 1 : 길 2 : 풀 3 : 워프 4 : 미끄럼 5 : NPC
*	워프 = 맵번호/x좌표 2자리/y좌표 2자리/3
*	NPC	 = 이미지번호/보는 방향(0~3)/5
*/

class map
{
private:
	int map_array[VERTICLE_LINE + 1][HORIZONTAL_LINE + 1];
public:
	bool IsMap;
	int map_number;			// 현재 맵 번호
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