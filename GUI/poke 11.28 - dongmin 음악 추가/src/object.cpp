#include "object.h"

// ��ü ����. ��� ����
void object::Init(int x, int y)
{
	this->x = x;
	this->y = y;
	fx = LENGTH * x;
	fy = LENGTH * y;
}

// ĳ���͸� ���ϴ� ��ġ�� ���� �ִ� �������� ����
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
// ��ü ����. ��� ����
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
// ĳ���� �ȴ� �ִϸ��̼� ������ִ� �Լ�
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
// ĳ���͸� ���ϴ� ��ġ�� ���� �ִ� �������� ����
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
// �ȼ���ǥ�迡�� �����̴� ��ü�� ���ϴ� ��ġ���� �������°�?
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