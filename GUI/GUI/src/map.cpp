#include "map.h"

void map::Init()
{
	map_number = 0;
	num_npc = 0;
	for (int i = 0; i < VERTICLE_LINE + 1; i++) 
	{
		for (int j = 0; j < HORIZONTAL_LINE + 1; j++) 
		{
			map_array[i][j] = 1;
			if (map_array[i][j] % 10 == 4)
			{
				num_npc++;
			}
		}
	}
}

// 00,00,00,0 7자리 이상의 수는 순서대로 맵번호, x좌표, y좌표, 3인 link 타일
int map::Link_Map(int *x, int *y)
{
	int link_num = map_array[*x][*y];
	map_number = link_num / 100000;
	*x = (link_num - map_number * 100000) / 1000;
	*y = (link_num - map_number * 100000 - (*x) * 1000) / 10;
	return map_number;
}

void map::Loading_Map(int *Map_DB)
{
	for (int i = 0; i < VERTICLE_LINE + 1; i++) 
	{
		for (int j = 0; j < HORIZONTAL_LINE + 1; j++) 
		{
			map_array[i][j] = Map_DB[i + (VERTICLE_LINE + 1) * j];
			if (map_array[i][j] % 10 == 4)
			{
				num_npc++;
			}
		}
	}
}

int map::Check_Map(int x, int y)
{
	return map_array[x][y] % 10;
}

int map::GetNum(int x, int y)
{
	return map_array[x][y];
}