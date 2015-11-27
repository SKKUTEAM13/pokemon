#include "object.h"

// ĳ���͸� ���ϴ� ��ġ�� ���� �ִ� �������� ����
void object::SetObjects(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
	animation = 0;
	IsLeft = true;
	tile = 0;
}
// �ȼ���ǥ�迡�� �����̴� ��ü�� ���ϴ� ��ġ���� �������°�?
bool object::Check_Stop()
{
	if (fx == x * LENGTH && fy == y * LENGTH)
	{
		animation = 0;
		return true;
	}
	return false;
}

bool object::Check_Direct(int input)
{
	if (direct != input)
	{
		direct = input;
		return false;
	}
	return true;
}
// ��ü ����. ��� ����
void object::Init(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
	animation = 0;
	direct = 3;
	tile = 0;
}
// ĳ���� �ȴ� �ִϸ��̼� ������ִ� �Լ�
bool object::WalkAnimation(int count)
{
	if (count < LENGTH / 4)
		return false;
	if (count == LENGTH / 4)
	{
		if (IsLeft)
		{
			animation = 1;
			IsLeft = false;
		}
		else if (!IsLeft)
		{
			animation = 2;
			IsLeft = true;
		}
	}
	else if (count > LENGTH * 3 / 4)
	{
		animation = 0;
		return false;
	}
	return true;
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