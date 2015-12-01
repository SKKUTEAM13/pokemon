/*
*	Version 12.02
*	��Ʋ, ġ��, ���� ���� ����.
*	Version 12.01
*	��ȭ ����, YesNo ����
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

#include "object.h"
#include "map.h"
#include "timer.h"
#include "BattleHandler.h"
#include "PokemonClass.h"
#include "data.h"
#include "winapi.h"
#include "glHandler.h"

people	player;										// �÷��̾� ����
object	arrow;
timer	Timer;

/* �츮�� ��� */
Pikachu pika(5);
GuGu	gugu(15);
GuGu	rocket1(4);

battleHandler	War;
NPCHandler		CurrentNPC;
glHandler		gl;
/* ȭ��ǥ, ȭ��ǥ ������ �� */

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

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity(); glEnable(GL_TEXTURE_2D);
	if (!battle) {
		if (intro){
			// ��Ʈ�� �̹��� �ݺ�
			gl.Set2DTexture(texture_intro[Map.map_number], 7, 5);
			gl.Print2DTextureQUADS(VERTICLE_LINE + 1, HORIZONTAL_LINE + 1);
		}
		else {
			// ��
			gl.Set2DTexture(texture_map[Map.map_number], 7, 5);
			gl.Print2DTextureQUADS(VERTICLE_LINE + 1, HORIZONTAL_LINE + 1);
		}
		glEnable(GL_BLEND);
		// NPC ���
		for (loop1 = 0; loop1 < Map.num_npc; loop1++)
		{
			gl.PrintPeople(Map.NPC[loop1]);
		}
		// ��� �׸��� ���
		if (player.tile == 2) {
			if (CountLoop % 2 == 0) {}
			else if (CountLoop < LENGTH) { animation += steps[adjust]; }
			else if (CountLoop < 2 * LENGTH) { animation -= steps[adjust]; }
			else if (CountLoop > 2 * LENGTH) {
				if (Map.Check_Map(player.x, player.y) == 2) { player.tile = 1; }
				else { player.tile = 0; }
				animation = 0;
			}
			glLoadIdentity();
			glTranslatef(player.fx + START_X * 1.0f, animation + player.fy + START_Y * 1.0f, 0.0f);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_char[14]);
			glBegin(GL_QUADS); glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
			glTexCoord2f(0.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
			glEnd();
			glBlendFunc(GL_ONE, GL_ONE); glBegin(GL_QUADS); glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
			glTexCoord2f(1.0f, 0.0f);	glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
			glTexCoord2f(0.0f, 0.0f);	glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
			glEnd();
		}
		gl.PrintPeople(player);
		// �ܵ� �ִϸ��̼�
		if (player.tile == 1)
		{
			glLoadIdentity();
			glTranslatef(player.fx + START_X * 1.0f, player.fy - 0.25 * LENGTH + START_Y * 1.0f, 0.0f);	
			int grass = 2;
			if (!player.Check_Stop()) { grass = (CountLoop - CountLoop / (LENGTH / 2)) / (LENGTH / 2); }
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_char[4]);
			glBegin(GL_QUADS); glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f((grass + 0) / 3.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);		// Top Left Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);		// Top Right Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);		// Bottom Right Of Player
			glTexCoord2f((grass + 0) / 3.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);		// Bottom Left Of Player
			glEnd(); 
			glBlendFunc(GL_ONE, GL_ONE); glBegin(GL_QUADS); glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f((grass + 0) / 3.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);		// Top Left Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);		// Top Right Of Player
			glTexCoord2f((grass + 1) / 3.0f, 0.0f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);		// Bottom Right Of Player
			glTexCoord2f((grass + 0) / 3.0f, 0.0f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);		// Bottom Left Of Player
			glEnd();
		}
		glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);

		if (isMenuOn)
		{
			// �޴� ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[0], 12.5, 5);
			gl.Print2DTextureQUADS(4, HORIZONTAL_LINE + 1);
			// ��Ʈ
			gl.SetFontInit(texture_font[0]);
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
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
		if (Talk)
		{
			// ��ȭâ ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[1], 7, 9);
			gl.Print2DTextureQUADS(VERTICLE_LINE + 1, 3);
			// ���� NPC�κ��� ���� ��� ���
			gl.SetFontInit(texture_font[0]);
			glPrint(1.5 * LENGTH + START_X * 1.0f,
				8.8 * LENGTH + START_Y * 1.0f, 1,
				CurrentNPC.GetData());
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
		if (YesNo)
		{
			// YesNo ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[2], 13, 6);
			gl.Print2DTextureQUADS(3, 3);
			// ��Ʈ
			glLoadIdentity(); gl.SetFontInit(texture_font[0]);
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
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
	}
	else if (battle) {
		glLoadIdentity();
		glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
		gl.PrintQUADS(VERTICLE_LINE + 1, HORIZONTAL_LINE + 1);
		// ��ī�� ����â ���
		glLoadIdentity(); glEnable(GL_TEXTURE_2D);
		gl.Set2DTexture(texture_window[5], 11.5, 5.5);
		gl.Print2DTextureQUADS(5, 2);
		// �� ���ϸ� ����â ���
		glLoadIdentity();
		gl.Set2DTexture(texture_window[6], 2.5, 1.3);
		gl.Print2DTextureQUADS(5, 1);
		// ��Ʈ
		glLoadIdentity(); gl.SetFontInit(texture_font[0]);
		// �� ���ϸ� �̸�, ����, HP
		glPrint(0.5 * LENGTH + START_X * 1.0f,
				0.0 * LENGTH + START_Y * 1.0f, 0,
				"%s|%d", gugu.getName(), 2);
		glPrint(0.8 * LENGTH + START_X * 1.0f,
				1.0 * LENGTH + START_Y * 1.0f, 0,
				"%d/ %d", gugu.getVital(), gugu.getFullVital());
		// ��ī�� �̸�, ����, HP
		glPrint(9.5 * LENGTH + START_X * 1.0f,
				4.5 * LENGTH + START_Y * 1.0f, 0,
				"%s|%d", pika.getName(), 5);
		glPrint(9.9 * LENGTH + START_X * 1.0f,	
				5.6 * LENGTH + START_Y * 1.0f, 0, 
				"%d/ %d", pika.getVital(), pika.getFullVital());
		glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		// �ؿ� �� ��ȭâ ���
		glLoadIdentity(); glEnable(GL_TEXTURE_2D);
		gl.Set2DTexture(texture_window[1], 7, 9);
		gl.Print2DTextureQUADS(VERTICLE_LINE + 1, 3);
		glDisable(GL_TEXTURE_2D);

		if (!skill) {
			// ��Ʋ �޴� ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[3], 11.5, 9);
			gl.Print2DTextureQUADS(6, 3);
			// ��Ʈ
			glLoadIdentity(); gl.SetFontInit(texture_font[0]);
			// ȭ��ǥ
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			// �޴�
			glPrint(9.5 * LENGTH + START_X * 1.0f,
				8.5 * LENGTH + START_Y * 1.0f, 1,
				"FIGHT  $&");
			glPrint(9.5 * LENGTH + START_X * 1.0f,
				9.5 * LENGTH + START_Y * 1.0f, 0,
				"PACK   RUN");
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
		else if (skill) {
			// ��ų ����Ʈ ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[4], 10.5, 8.5);
			gl.Print2DTextureQUADS(8, 4);
			// ��Ʈ
			glLoadIdentity(); gl.SetFontInit(texture_font[0]);
			// ȭ��ǥ
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			// ��ų ���
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				7.5 * LENGTH + START_Y * 1.0f, 0,
				"Thunder bolt");
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				8.5 * LENGTH + START_Y * 1.0f, 1,
				"Iron Tail");
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				9.5 * LENGTH + START_Y * 1.0f, 0,
				"-- --");
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
		if (!OK && BattleTalk) {
			// ���� �� ����ڰ� ���� �Ǵ� ���� ��ȭâ ���
			glLoadIdentity(); glEnable(GL_TEXTURE_2D);
			gl.Set2DTexture(texture_window[1], 7, 9);
			gl.Print2DTextureQUADS(VERTICLE_LINE + 1, 3);
			// ��Ʈ
			glLoadIdentity(); glEnable(GL_BLEND);
			gl.SetFontInit(texture_font[0]);
			// ���� ����
			if (BattleTalk == 1) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
						8.8 * LENGTH + START_Y * 1.0f, 1,
						"send out %s", gugu.getName());
			}
			// ����
			else if (BattleTalk == 2) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
						8.8 * LENGTH + START_Y * 1.0f, 1,
						"%s used %s", pika.getName(), pika.getSkill(Answer + 4));
			}
			// �İ�
			else if (BattleTalk == 3) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
						8.8 * LENGTH + START_Y * 1.0f, 1,
						"%s used %s", gugu.getName(), gugu.getSkill(RamdomSkill));
			}
			else if (BattleTalk == 4) {
				// ���� ����
				if (gameover) {
					glPrint(1.5 * LENGTH + START_X * 1.0f,
							8.8 * LENGTH + START_Y * 1.0f, 1,
							"I have no other pokemon");
				}
				// �̱�
				else {
					glPrint(1.5 * LENGTH + START_X * 1.0f,
							8.8 * LENGTH + START_Y * 1.0f, 1,
							"%s was defeated!", gugu.getName());
				}
			}
			glDisable(GL_BLEND); glDisable(GL_TEXTURE_2D);
		}
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
			CountLoop = 0;
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
					CountLoop = 0;			// ����
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

	CountLoop = 0;

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
						if (CountLoop > LENGTH && keys['Z'])
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
							CountLoop = LENGTH;
						}
						if (CountLoop % LENGTH == 0)
						{
							animation++;
							animation = animation % 6;
						}
						CountLoop += steps[adjust];
					}
					// �޴� �Ѽ� ���� ����
					if (isMenuOn)
					{
						if (keys['X']) {
							keys['X'] = 0;
							isMenuOn = false;
							interrupt = false;
							Map.Loading_Map(map_DB[Map.map_number]);
							CountLoop = LENGTH;
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
							CountLoop = LENGTH;
						}
						if (keys['Z']) {
							keys['Z'] = 0;
							YesNo = false;
							Answer = arrow.x - 12 + arrow.y - 5;
							arrow.SetObjects(20, 20);
							player.SetObjects(player.x, player.y);
							Map.Loading_Map(map_DB[Map.map_number]);
							CountLoop = LENGTH;
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
					if (!battle && Talk)
					{
						if (wait == 0) {
							if (keys['Z']) {
								keys['Z'] = 0;
								if (CurrentNPC.GetLink() == 4)
								{
									pika.Heal();
								}
								if (CurrentNPC.GetLink() == 3)
								{
									interrupt = battle = true;
									OK = false;
									BattleTalk = 1;
									arrow.SetObjects(9, 8);
									Map.Loading_Map(list_DB[0]);
								}
								else if (CurrentNPC.GetLink() == 2) {
									if (!YesNo && Answer == -1) {
										YesNo = true;
										arrow.SetObjects(12, 5);
										X_Answer = 12;
										Y_Answer = 5;
										Map.Loading_Map(list_DB[0]);
									}
									else if (Answer != -1) {
										if (Answer == 0) {
											CurrentNPC.SetYesNext();
											Answer = -1;
										}
										else if (Answer == 1) {
											CurrentNPC.SetNoNext();
											Answer = -1;
										}
									}
								}
								else {
									interrupt = Talk = CurrentNPC.GetLink();
									CurrentNPC.SetYesNext();
								}
							}
						}
						else if ((CountLoop % LENGTH == 0) && (wait > 0))
						{
							wait--;
						}
						else {
							CountLoop += steps[adjust];
						}
					}
					// ��Ʋ
					if (OK && battle && ((BattleTalk == 2) || (BattleTalk == 3)))
					{
						// �İ��� �ڵ�
						if (BattleTalk == 3) {
							RamdomSkill = (rand() % 2) + 1;
							War.opponentTurn(&pika, &gugu, RamdomSkill);
							if (0 >= pika.getVital()) {
								BattleTalk = 4;
								gameover = true;
							}
							OK = false;
							Answer = -1;
						}
						// X ���ý� ��ų â�̸� ��ųâ ��
						else if (keys['X']) {
							keys['X'] = 0;
							if (!skill) {
								interrupt = battle = false;
								arrow.SetObjects(20, 20);
								player.SetObjects(player.x, player.y);
								Map.Loading_Map(map_DB[Map.map_number]);
								CountLoop = LENGTH;
							}
							else if (skill) {
								skill = false;
								arrow.SetObjects(9, 8);
							}
						}
						/*	����.
						*	-3 : ��ų 1��, -2 : ��ų 2��
						*	 0 : �ο��		3 : x
						*	 1 : x			4 : ��������
						*/
						else if (keys['Z']) {
							keys['Z'] = 0;
							Answer = arrow.x - 9 + arrow.y - 8;
							if (OK && (Answer == -3 || Answer == -2)) {
								// ��ų ���� ������
								if (BattleTalk == 2) {
									skill = false;
									War.playerTurn(&pika, &gugu, Answer + 3);
									if (0 >= gugu.getVital()) {
										BattleTalk = 4;
									}
									OK = false;
								}
							}
							// �ο��
							else if (Answer == 0) {
								skill = true;
								arrow.SetObjects(7, 7);
								CountLoop = LENGTH;
							}
							// ��������
							else if (Answer == 4) {
								interrupt = battle = BattleTalk = OK = false;
								arrow.SetObjects(20, 20);
								player.SetObjects(player.x, player.y);
								Map.Loading_Map(map_DB[Map.map_number]);
								CountLoop = LENGTH;
								Answer = -1;
							}
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
					if (BattleTalk && !OK)
					{
						if (keys['X'] || keys['Z']) {
							keys['X'] = keys['Z'] = false;
							if (BattleTalk == 1) {
								OK = true;
								BattleTalk++;
							}
							else if (BattleTalk == 2) {
								OK = true;
								BattleTalk++;
							}
							else if (BattleTalk == 3) {
								OK = true;
								BattleTalk--;
								arrow.SetObjects(9, 8);
							}
							else if (BattleTalk == 4) {
								BattleTalk = 0;
								interrupt = battle = false;
								CountLoop = LENGTH;
								Answer = -1;
								arrow.SetObjects(20, 20);
								if (gameover)
								{
									/*	���� ����
									*	���� �ο�� ���� NoNext, HP ����, ���� HP ����
									*	���� ������ ��ġ ����, �� ����, npc ����
									*/
									CurrentNPC.SetNoNext();
									Map.DeleteNPC();
									pika.Heal(); gugu.Heal();
									gameover = Talk = false; 
									CountLoop = 0;
									Map.IsMap = true; 
									Map.map_number = 0;
									player.direct = 3; 
									player.x = 8; 
									player.y = 5;
									if (nowplaying != BGM_map[Map.map_number] + 1) {
										mciSendCommand(nowplaying, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
										mciSendCommand(nowplaying, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlay);
										nowplaying = BGM_map[Map.map_number] + 1;
										mciSendCommand(nowplaying, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
									}
								}
								else {
									interrupt = Talk = CurrentNPC.GetLink();
									CurrentNPC.SetYesNext();
								}
								player.SetObjects(player.x, player.y);
								Map.Loading_Map(map_DB[Map.map_number]);
							}
						}
					}
				}
				else {
					// ���������� �޴� �θ�
					if (keys['X'] && !player.WalkAnimation(CountLoop)) {
						isMenuOn = !isMenuOn;
						interrupt = true;
						arrow.SetObjects(11, 0);
						Map.Loading_Map(list_DB[0]);
						keys['X'] = 0;
					}
					if (keys['C'] && !player.WalkAnimation(CountLoop)) {
						interrupt = battle = true;
						OK = false;
						BattleTalk = 1;
						arrow.SetObjects(9, 8);
						Map.Loading_Map(list_DB[0]);
						keys['C'] = 0;
					}
					// npc ���ɱ�
					else if (keys['Z'] && !player.WalkAnimation(CountLoop)) {
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
								interrupt = Talk = true;
								keys['Z'] = 0;
								wait = 8;
								CountLoop = 0;
								Answer = -1;
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
							CountLoop = 0;
						}
						else
						{
							player.WalkAnimation(CountLoop);

							// Move player from (fx, fy) to (x, y)
							player.MoveObject(steps[adjust], CountLoop);
							CountLoop += steps[adjust];
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