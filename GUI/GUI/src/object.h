#pragma once

#define LENGTH 40

class object
{
public:
	int fx, fy;						// ĳ���� �ȼ� ��ǥ��
	int x, y;						// ĳ���� �� ��ǥ��
	int direct;						// ĳ���Ͱ� ���� ����
	bool IsLeft;					// �޹� ��������
	int animation;					//	0, 1, 2 ���� �޹� ������
	int tile;						// Ư�� Ÿ��

	bool Check_Stop();				// object.cpp �� ����
	bool Check_Direct(int input);
	void SetObjects(int x, int y);
	void Init(int x, int y);
	void WalkAnimation(int count);
	void MoveObject(int steps);
};
