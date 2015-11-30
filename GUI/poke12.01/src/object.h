#pragma once

#include <map>
#include <set>
#include <string>

#define LENGTH 40

class object
{
public:
	int fx, fy;						// ĳ���� �ȼ� ��ǥ��
	int x, y;						// ĳ���� �� ��ǥ��

	void Init(int x, int y);
	void SetObjects(int x, int y);
	void MoveObject(int steps);
	void MovementByKeyInput(int VK_INPUT);
};

class people : public object
{
public:
	int direct;						// ĳ���Ͱ� ���� ����
	bool IsLeft;					// �޹� ��������
	bool IsWalk;
	int animation;					//	0, 1, 2, 3 ���� �޹� ���� ������
	int tile;						// Ư�� Ÿ��
	int story;						// ���丮 ���࿡ ���� ��ȭ ������ ����
	int texture_number;

	void Init(int x, int y, int texture);
	void SetObjects(int x, int y);
	bool Check_Stop();				// object.cpp �� ����
	bool Check_Direct(int input);
	bool WalkAnimation(int count);
	void MoveObject(int steps, int count);
	void MovementByKeyInput(int VK_INPUT);
};
