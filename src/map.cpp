#include "map.h"

void pokemap::Init()
{
	map_number = 0;
	num_npc = 0;
	IsMap = true;
	for (int i = 0; i < VERTICLE_LINE + 1; i++) 
	{
		for (int j = 0; j < HORIZONTAL_LINE + 1; j++) 
		{
			map_array[i][j] = 1;
		}
	}
}

// 00,00,00,0 7자리 이상의 수는 순서대로 맵번호, x좌표, y좌표, 3인 link 타일
int pokemap::Link_Map(int *x, int *y)
{
	int link_num = map_array[*x][*y];
	map_number = link_num / 100000;
	*x = (link_num - map_number * 100000) / 1000;
	*y = (link_num - map_number * 100000 - (*x) * 1000) / 10;

	IsMap = true;
	return map_number;
}

void pokemap::Loading_Map(int *Map_DB)
{
	if(IsMap)
		num_npc = 0;
	for (int i = 0; i < VERTICLE_LINE + 1; i++) 
	{
		for (int j = 0; j < HORIZONTAL_LINE + 1; j++) 
		{
			map_array[i][j] = Map_DB[i + (VERTICLE_LINE + 1) * j];
			if (IsMap && (map_array[i][j] % 10 == 5))
			{
				InitNPC(map_array[i][j], i, j, num_npc);
				num_npc++;
			}
		}
	}
	IsMap = false;
}

int pokemap::Check_Map(int x, int y)
{
	return map_array[x][y] % 10;	// 0: 충돌, 1: 길, 2: 풀, 3: 워프, 4: 미끄럼
}

int pokemap::GetNum(int x, int y)
{
	return map_array[x][y];
}

void pokemap::InitNPC(int input, int x, int y, int loop)
{
	NPC[loop].story = (input / 10000);
	NPC[loop].texture_number = (input % 10000) / 100;
	NPC[loop].Init(x, y, NPC[loop].texture_number);
	NPC[loop].direct = (input % 100) / 10;
}

void pokemap::DeleteNPC()
{
	for (int i = 0; i < num_npc; i++)
	{
		NPC[i].texture_number = 10;
		NPC[i].Init(0, 0, 10);
		NPC[i].direct = 0;
	}
	num_npc = 0;
}