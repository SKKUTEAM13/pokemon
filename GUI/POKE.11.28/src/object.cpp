#include "object.h"

// 객체 생성. 모두 리셋
void object::Init(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
}

// 캐릭터를 원하는 위치에 보고 있던 방향으로 생성
void object::SetObjects(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
	//animation = 0;
	//IsLeft = true;
	//tile = 0;
}

void object::MoveObject(int steps)
{
	if (fx < x * LENGTH)	// Is Fine Position On X Axis Lower Than Intended Position?
	{
		fx += steps;		// If So, Increase The Fine X Position
	}
	if (fx > x * LENGTH)	// Is Fine Position On X Axis Greater Than Intended Position?
	{
		fx -= steps;		// If So, Decrease The Fine X Position
	}
	if (fy < y * LENGTH)	// Is Fine Position On Y Axis Lower Than Intended Position?
	{
		fy += steps;		// If So, Increase The Fine Y Position
	}
	if (fy > y * LENGTH)	// Is Fine Position On Y Axis Lower Than Intended Position?
	{
		fy -= steps;		// If So, Decrease The Fine Y Position
	}
}

/* people */
// 객체 생성. 모두 리셋
void people::Init(int x, int y, int texture)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
	animation = 0;
	direct = 3;
	tile = 0;
	texture_number = texture;
}
// 캐릭터 걷는 애니메이션 만들어주는 함수
bool people::WalkAnimation(int count)
{
	if (count < LENGTH / 4)
		return false;
	if (count == LENGTH / 4)
	{
		IsLeft = !IsLeft;
		animation++;
	}
	else if (count > LENGTH * 3 / 4)
	{
		animation = 0 + 2 * IsLeft;
		return false;
	}
	return true;
}
// 캐릭터를 원하는 위치에 보고 있던 방향으로 생성
void people::SetObjects(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
	animation = 0;
	IsLeft = true;
	tile = 0;
}
// 픽셀좌표계에서 움직이는 객체가 원하는 위치까지 움직였는가?
bool people::Check_Stop()
{
	if (fx == x * LENGTH && fy == y * LENGTH)
	{
		animation = 0;
		return true;
	}
	return false;
}

bool people::Check_Direct(int input)
{
	if (direct != input)
	{
		direct = input;
		return false;
	}
	return true;
}