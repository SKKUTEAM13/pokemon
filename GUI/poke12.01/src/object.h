#pragma once

#include <map>
#include <set>
#include <string>

#define LENGTH 40

class object
{
public:
	int fx, fy;						// 캐릭터 픽셀 좌표계
	int x, y;						// 캐릭터 맵 좌표계

	void Init(int x, int y);
	void SetObjects(int x, int y);
	void MoveObject(int steps);
	void MovementByKeyInput(int VK_INPUT);
};

class people : public object
{
public:
	int direct;						// 캐릭터가 보는 방향
	bool IsLeft;					// 왼발 차례인지
	bool IsWalk;
	int animation;					//	0, 1, 2, 3 차렷 왼발 차렷 오른발
	int tile;						// 특수 타일
	int story;						// 스토리 진행에 맞춰 대화 진행을 위해
	int texture_number;

	void Init(int x, int y, int texture);
	void SetObjects(int x, int y);
	bool Check_Stop();				// object.cpp 에 설명
	bool Check_Direct(int input);
	bool WalkAnimation(int count);
	void MoveObject(int steps, int count);
	void MovementByKeyInput(int VK_INPUT);
};
