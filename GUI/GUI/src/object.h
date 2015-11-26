#pragma once

#define LENGTH 40

class object
{
public:
	int fx, fy;						// 캐릭터 픽셀 좌표계
	int x, y;						// 캐릭터 맵 좌표계
	int direct;						// 캐릭터가 보는 방향
	bool IsLeft;					// 왼발 차례인지
	int animation;					//	0, 1, 2 차렷 왼발 오른발
	int tile;						// 특수 타일

	bool Check_Stop();				// object.cpp 에 설명
	bool Check_Direct(int input);
	void SetObjects(int x, int y);
	void Init(int x, int y);
	void WalkAnimation(int count);
	void MoveObject(int steps);
};
