/*
*	Version 12.01
*	��ȭ ����, YesNo ����
*	Version 11.29 
*	NPC �߰�(����, �ؽ�Ʈ ���� ���� ���� ���丮 �߰�)
*	���� �߰� 
*	�޴�
*	Animation and MAP
*	OpenGL, MAP, BMP
*
*/
#pragma comment(lib, "winmm.lib")

#include <stdio.h>			// Header File For Standard Input / Output
#include <gl/freeglut.h>	// Header File For OpenGL 
#include <mmsystem.h>
#include <Digitalv.h>
#include <iostream>
#include <string>
#include "SOIL.h"			// Header File For Loading BMP Image

int		loop1;				// Generic Loop1
int		loop2;				// Generic Loop2

#include "data.h"
#include "winapi.h"
#include "map.h"
#include "object.h"
#include "timer.h"

//////////////////// ���� ��� �Լ�/////////////////
MCI_OPEN_PARMS      mciOpen; //���� ������ �ε�
MCI_PLAY_PARMS       mciPlay; //���� ������ ���
MCI_STATUS_PARMS   mciStatus; //���� ������ ����

DWORD BGM[NUM_BGM + 2];
UINT wDeviceID = 0;
int nowplaying = 0;

DWORD LoadMP3(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;

	mciOpen.lpstrDeviceType = "MPEGVideo";
	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (Result)
		return Result;

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}

int		adjust = 0;									// �ӵ� ����
int		steps[6] = { 1, 2, 4, 5, 10, 20 };			// �ѹ��� ������ �ȼ� �� ����. adjust�� ����.
int		count = LENGTH;
int		animation = 0;								// people Ŭ������ �ƴ� �ƴ� �͵� �ִϸ��̼� ��
int		isMenuOn = 0;								// �޴��� �Ѱ� ���� ���ؼ� �ʿ�!
int		TalkNPC = -1;
int 	wait = 0;
int		Answer = -1;
int		X_Answer, Y_Answer;

bool	intro = true;
bool	Talk = false;
bool	YesNo = false;
bool	interrupt = true;									// �ܺ� �Է��� �����ų� zŰ�� �������� �����ϸ� true
bool	IsJump = false;
bool	battle = false;

/* Unit In Game */
people	player;										// �÷��̾� ����
map		Map;
timer	Timer;

/* ȭ��ǥ, ȭ��ǥ ������ �� */
object	arrow;

GLvoid glPrintPeople(people person)
{
	glLoadIdentity();
	glTranslatef(person.fx + START_X * 1.0f, person.fy - 0.25 * LENGTH + START_Y * 1.0f, 0.0f);	
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture(GL_TEXTURE_2D, texture_char[person.texture_number + person.direct]);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
	glEnd();
	glBlendFunc(GL_ONE, GL_ONE);
	glBegin(GL_QUADS);																				
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);	
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.0f);	glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.0f);	glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
	glEnd();
}

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	// map
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	if (!battle) {
		if (intro)
		{
			glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);

			glBindTexture(GL_TEXTURE_2D, texture_intro[Map.map_number]);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glEnd();
		}
		else {
			glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);

			glBindTexture(GL_TEXTURE_2D, texture_map[Map.map_number]);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glEnd();
		}
		glEnable(GL_BLEND);

		for (loop1 = 0; loop1 < Map.num_npc; loop1++)
		{
			glPrintPeople(Map.NPC[loop1]);
		}
		if (player.tile == 2) {
			if (count % 2 == 0) {}
			else if (count < LENGTH)
			{
				animation += steps[adjust];
			}
			else if (count < 2 * LENGTH)
			{
				animation -= steps[adjust];
			}
			else if (count > 2 * LENGTH)
			{
				if (Map.Check_Map(player.x, player.y) == 2)
					player.tile = 1;
				else player.tile = 0;
				animation = 0;
			}
			glLoadIdentity();
			glTranslatef(player.fx + START_X * 1.0f, animation + player.fy + START_Y * 1.0f, 0.0f);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_char[14]);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
			glTexCoord2f(0.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
			glEnd();
			glBlendFunc(GL_ONE, GL_ONE);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.0f);	glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
			glTexCoord2f(0.0f, 0.0f);	glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
			glEnd();
		}
		glPrintPeople(player);

		if (player.tile == 1)
		{
			glLoadIdentity();
			glTranslatef(player.fx + START_X * 1.0f, player.fy - 0.25 * LENGTH + START_Y * 1.0f, 0.0f);	// Move To The Fine Player Position

			int grass = 2;
			if (!player.Check_Stop())
			{
				grass = (count - count / (LENGTH / 2)) / (LENGTH / 2);
			}
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_char[4]);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f((grass + 0) / 3.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);		// Top Left Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);		// Top Right Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);		// Bottom Right Of Player
			glTexCoord2f((grass + 0) / 3.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);		// Bottom Left Of Player
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);

			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f((grass + 0) / 3.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);		// Top Left Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);		// Top Right Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.0f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);		// Bottom Right Of Player
			glTexCoord2f((grass + 0) / 3.0f, 0.0f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);		// Bottom Left Of Player
			glEnd();
		}

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		if (isMenuOn)
		{
			glLoadIdentity();
			glTranslatef(12.5 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture_window[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 4 / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * 4 / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * 4 / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 4 / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
			glEnd();

			glLoadIdentity();
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_font[0]);
			glColor3f(1.0f, 1.0f, 1.0f);
			// ȭ��ǥ
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			// �޴�
			glPrint(11.5 * LENGTH + START_X * 1.0f,
				0.5 * LENGTH + START_Y * 1.0f, 0,
				"Player");
			glPrint(11.5 * LENGTH + START_X * 1.0f,
				1.5 * LENGTH + START_Y * 1.0f, 0,
				"Exit");

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}
	if (Talk)
	{
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(7 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glEnd();

		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, texture_font[0]);
		glColor3f(1.0f, 1.0f, 1.0f);

		glPrint(1.5 * LENGTH + START_X * 1.0f,
			8.8 * LENGTH + START_Y * 1.0f, 1,
			talk_poke[(Map.NPC[TalkNPC].story)].data);

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	if (YesNo)
	{
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(13 * LENGTH + START_X * 1.0f, 6 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 3 / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * 3 / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * 3 / 2, LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 3 / 2, LENGTH * 3 / 2);
		glEnd();

		glLoadIdentity();
		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, texture_font[0]);
		glColor3f(1.0f, 1.0f, 1.0f);
		// ȭ��ǥ
		glPrint(START_X + arrow.x * LENGTH,
			START_Y + (arrow.y + 0.5)* LENGTH, 1,
			"/");
		// �޴�
		glPrint(12.5 * LENGTH + START_X * 1.0f,
			5.5 * LENGTH + START_Y * 1.0f, 0,
			"Yes");
		glPrint(12.5 * LENGTH + START_X * 1.0f,
			6.5 * LENGTH + START_Y * 1.0f, 0,
			"No");

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	if (battle) {
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(7 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glEnd();

		glLoadIdentity();
		glTranslatef(11.5 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 6 / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * 6 / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * 6 / 2, LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 6 / 2, LENGTH * 3 / 2);
		glEnd();

		glLoadIdentity();
		glEnable(GL_BLEND);
		glPrint(9.5 * LENGTH + START_X * 1.0f,
			8.5 * LENGTH + START_Y * 1.0f, 1,
			"FIGHT  $&");
		glPrint(9.5 * LENGTH + START_X * 1.0f,
			9.5 * LENGTH + START_Y * 1.0f, 0,
			"PACK   RUN");
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	return true;
}

void object::MovementByKeyInput(int VK_INPUT)
{
	// VK	  ( LEFT : 37, UP : 38, RIGHT : 39, DOWN : 40 )
	// Direct ( LEFT :  0, UP :  1, RIGHT :  2, DOWN :  3 )
	
	if (keys[VK_INPUT]) 
	{
		int DirectKey = VK_INPUT - VK_LEFT;
		int X_DirectKey = (DirectKey - 1) % 2;
		int Y_DirectKey = (DirectKey - 2) % 2;

		if ((y + Y_DirectKey <= HORIZONTAL_LINE) &&						// �̵� �� ��ǥ �ʹ��� ������ x�� 0~14, y�� 0~10���� Ȯ�� 
			(x + X_DirectKey <= VERTICLE_LINE) &&
			(y + Y_DirectKey >= 0) &&
			(x + X_DirectKey >= 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 0)) // ���� �浹 Ÿ������ �ƴ��� �˻�
		{
			x += X_DirectKey;
			y += Y_DirectKey;

			// 4�� Ÿ���� �̲������� Ÿ��
			while (Map.Check_Map(x, y) == 4)
			{
				x += X_DirectKey;
				y += Y_DirectKey;
			}
		}
	}
}

void people::MovementByKeyInput(int VK_INPUT)
{
	// VK	  ( LEFT : 37, UP : 38, RIGHT : 39, DOWN : 40 )
	// Direct ( LEFT :  0, UP :  1, RIGHT :  2, DOWN :  3 )
	if (!Check_Stop())											// ����°�
		return;

	if (keys[VK_INPUT])
	{
		int DirectKey = VK_INPUT - VK_LEFT;
		int X_DirectKey = (DirectKey - 1) % 2;
		int Y_DirectKey = (DirectKey - 2) % 2;

		if (!Check_Direct(DirectKey)) { return; }
		else if (
			(y + Y_DirectKey <= HORIZONTAL_LINE) &&						// �̵� �� ��ǥ �ʹ��� ������ x�� 0~14, y�� 0~10���� Ȯ�� 
			(x + X_DirectKey <= VERTICLE_LINE) &&
			(y + Y_DirectKey >= 0) &&
			(x + X_DirectKey >= 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 5))		// ���� �浹 Ÿ������ �ƴ��� �˻�
		{
			if ((Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) == 4) &&
				((Map.map_array[x + X_DirectKey][y + Y_DirectKey] / 10) != 0) &&
				(Map.map_array[x + X_DirectKey][y + Y_DirectKey] / 10) % 4 != player.direct)
				return;
			x += X_DirectKey;
			y += Y_DirectKey;
			count = 0;
			// �ܵ� Ÿ�Ͽ� ���� ĳ�������� �ܵ� �ִϸ��̼� �߰�
			if (Map.Check_Map(x, y) == 2)
			{
				tile = 1;
			}
			else { tile = 0; }
			// 4�� Ÿ���� �̲������� Ÿ��
			if (Map.Check_Map(x, y) == 4)
			{
				if (Map.map_array[x][y] / 10 == 0)
				{	// ���� ������ ������ �̲�����
					while (Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) == 4)
					{
						x += X_DirectKey;
						y += Y_DirectKey;
					}
					if (Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) == 1)
					{
						x += X_DirectKey;
						y += Y_DirectKey;
					}
				}
				// 4 �տ� ���� ������ ���
				else {
					x += X_DirectKey;
					y += Y_DirectKey;

					tile = 2;			// ���� �ִϸ��̼� ��
					count = 0;			// ����
				}
			}
		}
	}
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows message Structure
	bool	done = false;
	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = false;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("pokemon", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	arrow.Init(20, 20);
	player.Init(20, 20, 0);
	Timer = Timer.TimerInit();
	// ���� �ε�
	for (loop1 = 0; loop1 < NUM_BGM; loop1++) {
		BGM[loop1] = LoadMP3(hWnd, path_BGM[loop1]);
	}
	BGM[0] = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

	count = 0;

	while (!done)									// Loop That Runs While done=FALSE
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		// Is There A Message Waiting?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = true;
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			float start = Timer.TimerGetTime();		// Grab Timer Value Before We Draw

			// Draw The Scene. Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((!DrawGLScene() && active) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done = true;						// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			while (Timer.TimerGetTime() < start + float(steps[adjust] * 4.0f)) {}	// Waste Cycles On Fast Systems

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = false;				// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;			// Toggle Fullscreen / Windowed Mode
													// Recreate Our OpenGL Window
				if (!CreateGLWindow("pokemon", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}

			if (active)								// If Programs Active Move Objects
			{
				if (interrupt)
				{
					// ��Ʈ�η� ���� ���� ����
					if (intro)
					{
						Map.map_number = animation;
						// �߰� �Է� ������ ���� ����
						if (count > LENGTH && keys['Z'])
						{
							mciSendCommand(1, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
							mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
							nowplaying = 2;
							interrupt = false;
							intro = false;

							// ���� ����
							Map.IsMap = true;
							Map.Loading_Map(map_DB[0]);
							player.SetObjects(3, 2);
							Map.map_number = 0;
							animation = 0;
							count = LENGTH;
						}
						if (count % LENGTH == 0)
						{
							animation++;
							animation = animation % 6;
						}
						count += steps[adjust];
					}
					// �޴� �Ѽ� ���� ����
					if (isMenuOn)
					{
						if (keys['X']) {
							keys['X'] = 0;
							isMenuOn = false;
							interrupt = false;
							Map.Loading_Map(map_DB[Map.map_number]);
							count = LENGTH;
							arrow.SetObjects(20, 20);
							player.SetObjects(player.x, player.y);
						}
						else
						{
							arrow.MovementByKeyInput(VK_LEFT);
							arrow.MovementByKeyInput(VK_UP);
							arrow.MovementByKeyInput(VK_RIGHT);
							arrow.MovementByKeyInput(VK_DOWN);
							arrow.SetObjects(arrow.x, arrow.y);
						}
					}
					// Yes No
					if (YesNo)
					{
						if (keys['X']) {
							keys['X'] = 0;
							YesNo = false;
							Answer = 1;
							player.SetObjects(player.x, player.y);
							Map.Loading_Map(map_DB[Map.map_number]);
							count = LENGTH;
						}
						if (keys['Z']) {
							keys['Z'] = 0;
							YesNo = false;
							Answer = arrow.x - 12 + arrow.y - 5;
							arrow.SetObjects(20, 20);
							player.SetObjects(player.x, player.y);
							Map.Loading_Map(map_DB[Map.map_number]);
							count = LENGTH;
						}
						else
						{
							arrow.MovementByKeyInput(VK_LEFT);
							arrow.MovementByKeyInput(VK_UP);
							arrow.MovementByKeyInput(VK_RIGHT);
							arrow.MovementByKeyInput(VK_DOWN);
							arrow.SetObjects(arrow.x, arrow.y);
						}
					}
					// ��ȭ interrupt
					if (Talk)
					{
						if (wait == 0) {
							if (keys['Z']) {
								keys['Z'] = 0;
								
								if (talk_poke[Map.NPC[TalkNPC].story].link > 1) {
									if (!YesNo && Answer == -1) {
										YesNo = true;
										arrow.SetObjects(12, 5);
										X_Answer = 12;
										Y_Answer = 5;
										Map.Loading_Map(list_DB[0]);
									}
									else if (Answer != -1) {
										if (Answer == 0) {
											interrupt = Talk = true;
											Map.NPC[TalkNPC].story = talk_poke[Map.NPC[TalkNPC].story].YesNext;
											Answer = -1;
										}
										else if (Answer == 1) {
											interrupt = Talk = talk_poke[Map.NPC[TalkNPC].story].link;
											Map.NPC[TalkNPC].story = talk_poke[Map.NPC[TalkNPC].story].NoNext;
											Answer = -1;
										}
									}
								}
								else {
									interrupt = Talk = talk_poke[Map.NPC[TalkNPC].story].link;
									Map.NPC[TalkNPC].story = talk_poke[Map.NPC[TalkNPC].story].YesNext;
								}
							}
						}
						else if ((count % LENGTH == 0) && (wait > 0))
						{
							wait--;
						}
						else {
							count += steps[adjust];
						}
					}

				}
				else {
					// ���������� �޴� �θ�
					if (keys['X'] && !player.WalkAnimation(count)) {
						isMenuOn = !isMenuOn;
						interrupt = true;
						arrow.SetObjects(11, 0);
						Map.Loading_Map(list_DB[0]);
						keys['X'] = 0;
					}
					
					// npc ���ɱ�
					else if (keys['Z'] && !player.WalkAnimation(count)) {
						// z �������� ���� NPC ���� Ȯ��
						if (Map.Check_Map(player.x + (player.direct - 1) % 2, player.y + (player.direct - 2) % 2) == 5) {
							// �´ٸ� ������ Ž��
							for (loop1 = 0; loop1 < Map.num_npc; loop1++) {
								if ((Map.NPC[loop1].x == player.x + (player.direct - 1) % 2) && 
									(Map.NPC[loop1].y == player.y + (player.direct - 2) % 2)) {
									TalkNPC = loop1;
									Map.NPC[loop1].Check_Direct((player.direct + 2) % 4);
									break;
								}
							}
							if (TalkNPC != -1) {
								interrupt = true;
								Talk = true;
								keys['Z'] = 0;
								wait = 8;
								count = 0;
							}
						}
						else TalkNPC = -1;
					}
					else {
						//����Ű �Է� ������ ������
						player.MovementByKeyInput(VK_LEFT);
						player.MovementByKeyInput(VK_UP);
						player.MovementByKeyInput(VK_RIGHT);
						player.MovementByKeyInput(VK_DOWN);

						if (Map.Check_Map(player.x, player.y) == 3)
						{
							Map.DeleteNPC();
							Map.Link_Map(&(player.x), &(player.y));
							Map.Loading_Map(map_DB[Map.map_number]);
							player.SetObjects(player.x, player.y);
							if (nowplaying != BGM_map[Map.map_number] + 1)
							{
								mciSendCommand(nowplaying, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
								mciSendCommand(nowplaying, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlay);
								nowplaying = BGM_map[Map.map_number] + 1;
								mciSendCommand(nowplaying, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
							}
							count = 0;
						}
						else
						{
							player.WalkAnimation(count);

							// Move player from (fx, fy) to (x, y)
							player.MoveObject(steps[adjust], count);
							count += steps[adjust];
						}
					}
				}
			}
		}
	}

	//Shutdown
	if (wDeviceID > 0) mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	KillGLWindow();
	return (msg.wParam);
}