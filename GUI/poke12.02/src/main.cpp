/*
*	Version 12.01
*	대화 업뎃, YesNo 업뎃
*	Version 11.29 
*	NPC 추가(방향, 텍스트 지정 가능 추후 스토리 추가)
*	색깔 추가 
*	메뉴
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
#include "BattleHandler.h"
#include "PokemonClass.h"

//////////////////// 음악 재생 함수/////////////////
MCI_OPEN_PARMS      mciOpen; //음악 파일을 로드
MCI_PLAY_PARMS       mciPlay; //음악 파일을 재생
MCI_STATUS_PARMS   mciStatus; //음악 파일의 상태

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

int		adjust = 0;									// 속도 조절
int		steps[6] = { 1, 2, 4, 5, 10, 20 };			// 한번에 실행할 픽셀 수 조절. adjust로 정함.
int		CountLoop = LENGTH;
int		animation = 0;								// people 클래스가 아닌 아닌 것들 애니매이션 용
int		isMenuOn = 0;								// 메뉴의 켜고 끔을 위해서 필요!
int		TalkNPC = -1;
int 	wait = 0;
int		Answer = -1;
int		X_Answer, Y_Answer;
int		BattleTalk = 0;
int		RamdomSkill;

bool	intro = true;
bool	Talk = false;
bool	YesNo = false;
bool	interrupt = true;									// 외부 입력이 들어오거나 z키를 눌렀을때 반응하면 true
bool	IsJump = false;
bool	battle = false;
bool	skill = false;
bool	gameover = false;

/* Unit In Game */
people	player;										// 플레이어 선언
pokemap	Map;
timer	Timer;

/* 우리의 희망 */
Pikachu pika(5);
GuGu	gugu(2);
battleHandler War;

/* 화살표, 화살표 움직일 맵 */
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
			if (CountLoop % 2 == 0) {}
			else if (CountLoop < LENGTH)
			{
				animation += steps[adjust];
			}
			else if (CountLoop < 2 * LENGTH)
			{
				animation -= steps[adjust];
			}
			else if (CountLoop > 2 * LENGTH)
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
				grass = (CountLoop - CountLoop / (LENGTH / 2)) / (LENGTH / 2);
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
			glEnable(GL_TEXTURE_2D);
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
			// 화살표
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			// 메뉴
			glPrint(11.5 * LENGTH + START_X * 1.0f,
				0.5 * LENGTH + START_Y * 1.0f, 0,
				"Player");
			glPrint(11.5 * LENGTH + START_X * 1.0f,
				1.5 * LENGTH + START_Y * 1.0f, 0,
				"Exit");

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
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
			// 화살표
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			// 메뉴
			glPrint(12.5 * LENGTH + START_X * 1.0f,
				5.5 * LENGTH + START_Y * 1.0f, 0,
				"Yes");
			glPrint(12.5 * LENGTH + START_X * 1.0f,
				6.5 * LENGTH + START_Y * 1.0f, 0,
				"No");

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
	}
	else if (battle) {
		glLoadIdentity();
		glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glEnd();

		
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, texture_font[0]);
		glPrint(1.5 * LENGTH + START_X * 1.0f,
				0.5 * LENGTH + START_Y * 1.0f, 0,
				"%s|%d", gugu.getName(), 2);
		glPrint(1.5 * LENGTH + START_X * 1.0f,
				1.5 * LENGTH + START_Y * 1.0f, 0,
				"%d / %d", gugu.getVital(), gugu.getFullVital());
		glPrint(10.5 * LENGTH + START_X * 1.0f,
				4.5 * LENGTH + START_Y * 1.0f, 0,
				"%s|%d", pika.getName(), 5);
		glPrint(10.5 * LENGTH + START_X * 1.0f,	
				5.5 * LENGTH + START_Y * 1.0f, 0, 
				"%d / %d", pika.getVital(), pika.getFullVital());
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);


		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(7 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[1]);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, LENGTH * 3 / 2);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		if (!skill) {
			glEnable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTranslatef(11.5 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture_window[3]);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 6 / 2, -LENGTH * 3 / 2);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * 6 / 2, -LENGTH * 3 / 2);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * 6 / 2, LENGTH * 3 / 2);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 6 / 2, LENGTH * 3 / 2);
			glEnd();

			glLoadIdentity();
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_font[0]);
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			glPrint(9.5 * LENGTH + START_X * 1.0f,
				8.5 * LENGTH + START_Y * 1.0f, 1,
				"FIGHT  $&");
			glPrint(9.5 * LENGTH + START_X * 1.0f,
				9.5 * LENGTH + START_Y * 1.0f, 0,
				"PACK   RUN");
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		else if (skill) {
			glEnable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTranslatef(10.5 * LENGTH + START_X * 1.0f, 8.5 * LENGTH + START_Y * 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture_window[4]);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 8 / 2, -LENGTH * 4 / 2);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(LENGTH * 8 / 2, -LENGTH * 4 / 2);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(LENGTH * 8 / 2, LENGTH * 4 / 2);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 8 / 2, LENGTH * 4 / 2);
			glEnd();

			glLoadIdentity();
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, texture_font[0]);
			glPrint(START_X + arrow.x * LENGTH,
				START_Y + (arrow.y + 0.5)* LENGTH, 1,
				"/");
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				7.5 * LENGTH + START_Y * 1.0f, 0,
				"Thunder bolt");
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				8.5 * LENGTH + START_Y * 1.0f, 1,
				"Iron Tail");
			glPrint(7.5 * LENGTH + START_X * 1.0f,
				9.5 * LENGTH + START_Y * 1.0f, 0,
				"-- --");
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		else if (BattleTalk) {
			glLoadIdentity();
			glEnable(GL_TEXTURE_2D);
			glTranslatef(7 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture_window[1]);
			glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
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
			if (BattleTalk == 1) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
					8.8 * LENGTH + START_Y * 1.0f, 1,
					"send out %s", gugu.getName());
			}
			else if (BattleTalk == 2) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
					8.8 * LENGTH + START_Y * 1.0f, 1,
					"%s used %s", pika.getName(), pika.getSkill(Answer + 3));
			}
			else if (BattleTalk == 3) {
				glPrint(1.5 * LENGTH + START_X * 1.0f,
					8.8 * LENGTH + START_Y * 1.0f, 1,
					"%s used %s", gugu.getName(), gugu.getSkill(RamdomSkill));
			}
			else if (BattleTalk == 4) {
				if (gameover) {
					glPrint(1.5 * LENGTH + START_X * 1.0f,
						8.8 * LENGTH + START_Y * 1.0f, 1,
						"I have no other pokemon");
				}
				else {
					glPrint(1.5 * LENGTH + START_X * 1.0f,
						8.8 * LENGTH + START_Y * 1.0f, 1,
						"%s was defeated!", gugu.getName());
				}
			}
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
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

		if ((y + Y_DirectKey <= HORIZONTAL_LINE) &&						// 이동 후 좌표 맵범위 안쪽인 x가 0~14, y가 0~10인지 확인 
			(x + X_DirectKey <= VERTICLE_LINE) &&
			(y + Y_DirectKey >= 0) &&
			(x + X_DirectKey >= 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 0)) // 맵이 충돌 타일인지 아닌지 검사
		{
			x += X_DirectKey;
			y += Y_DirectKey;

			// 4번 타일은 미끄러지는 타일
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
	if (!Check_Stop())											// 멈췄는가
		return;

	if (keys[VK_INPUT])
	{
		int DirectKey = VK_INPUT - VK_LEFT;
		int X_DirectKey = (DirectKey - 1) % 2;
		int Y_DirectKey = (DirectKey - 2) % 2;

		if (!Check_Direct(DirectKey)) { return; }
		else if (
			(y + Y_DirectKey <= HORIZONTAL_LINE) &&						// 이동 후 좌표 맵범위 안쪽인 x가 0~14, y가 0~10인지 확인 
			(x + X_DirectKey <= VERTICLE_LINE) &&
			(y + Y_DirectKey >= 0) &&
			(x + X_DirectKey >= 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 0) &&
			(Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) != 5))		// 맵이 충돌 타일인지 아닌지 검사
		{
			if ((Map.Check_Map(x + X_DirectKey, y + Y_DirectKey) == 4) &&
				((Map.map_array[x + X_DirectKey][y + Y_DirectKey] / 10) != 0) &&
				(Map.map_array[x + X_DirectKey][y + Y_DirectKey] / 10) % 4 != player.direct)
				return;
			x += X_DirectKey;
			y += Y_DirectKey;
			CountLoop = 0;
			// 잔디 타일에 들어가면 캐릭터한테 잔디 애니메이션 추가
			if (Map.Check_Map(x, y) == 2)
			{
				tile = 1;
			}
			else { tile = 0; }
			// 4번 타일은 미끄러지는 타일
			if (Map.Check_Map(x, y) == 4)
			{
				if (Map.map_array[x][y] / 10 == 0)
				{	// 얼음 끝나기 전까지 미끄러짐
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
				// 4 앞에 숫자 있으면 언덕
				else {
					x += X_DirectKey;
					y += Y_DirectKey;

					tile = 2;			// 점프 애니메이션 용
					CountLoop = 0;			// 시작
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
	// 음악 로딩
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
				if (gameover)
				{
					interrupt = false;
					Map.map_number = 0;
					Map.Loading_Map(map_DB[Map.map_number]);
					CountLoop = LENGTH;
					arrow.SetObjects(20, 20);
					player.x = 8;
					player.y = 5;
					player.direct = 3;
					player.SetObjects(player.x, player.y);
				}
				if (interrupt)
				{
					// 인트로로 인한 게임 정지
					if (intro)
					{
						Map.map_number = animation;
						// 추가 입력 받으면 게임 시작
						if (CountLoop > LENGTH && keys['Z'])
						{
							mciSendCommand(1, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
							mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
							nowplaying = 2;
							interrupt = false;
							intro = false;

							// 게임 셋팅
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
					// 메뉴 켜서 게임 정지
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
					// 대화 interrupt
					if (Talk)
					{
						if (wait == 0) {
							if (keys['Z']) {
								keys['Z'] = 0;
								
								if (talk_poke[Map.NPC[TalkNPC].story].link == 2) {
									if (!YesNo && Answer == -1) {
										YesNo = true;
										arrow.SetObjects(12, 5);
										X_Answer = 12;
										Y_Answer = 5;
										Map.Loading_Map(list_DB[0]);
									}
									else if (Answer != -1) {
										if (Answer == 0) {
											Map.NPC[TalkNPC].story = talk_poke[Map.NPC[TalkNPC].story].YesNext;
											Answer = -1;
										}
										else if (Answer == 1) {
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
						else if ((CountLoop % LENGTH == 0) && (wait > 0))
						{
							wait--;
						}
						else {
							CountLoop += steps[adjust];
						}
					}
					if (BattleTalk)
					{
						if (keys['X'] || keys['Z']) {
							keys['X'] = keys['Z'] = false;
							if (BattleTalk == 1) {
								BattleTalk++;
							}
							else if(BattleTalk == 2) {
								BattleTalk++;
							}
							else if (BattleTalk == 3) {
								BattleTalk--;
							}
							else if (BattleTalk == 4) {
								BattleTalk = 0;
							}
						}

					}
					if (battle && ((BattleTalk == 2) || (BattleTalk == 3)))
					{
						if (keys['X']) {
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
						if (keys['Z']) {
							keys['Z'] = 0;
							Answer = arrow.x - 9 + arrow.y - 8;
							if (Answer == -3 || Answer == -2) {
								// 스킬 선택 했으면
								if (BattleTalk == 2) {
									skill = false;
									War.playerTurn(&pika, &gugu, Answer + 3);
									if (0 >= gugu.getVital()) {
										interrupt = battle = false;
										BattleTalk = 4;
										Answer = -1;
									}
								}
								else if (BattleTalk == 3) {
									if (battle) {
										RamdomSkill = (rand() % 2) + 1;
										War.opponentTurn(&pika, &gugu, RamdomSkill);
										if (0 >= pika.getVital()) {
											interrupt = battle = false;
											BattleTalk = 4;
											gameover = true;
										}
									}
									Answer = -1;
								}
								arrow.SetObjects(9, 8);
							}
							else if (Answer == 0) {
								skill = true;
								arrow.SetObjects(7, 7);
								CountLoop = LENGTH;
							}
							else if (Answer == 4) {
								interrupt = battle = false;
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
							keys[VK_LEFT] = false;
							keys[VK_UP] = false;
							keys[VK_RIGHT] = false;
							keys[VK_DOWN] = false;
							arrow.SetObjects(arrow.x, arrow.y);
						}
					}
				}
				else {
					// 멈춰있을때 메뉴 부름
					if (keys['X'] && !player.WalkAnimation(CountLoop)) {
						isMenuOn = !isMenuOn;
						interrupt = true;
						arrow.SetObjects(11, 0);
						Map.Loading_Map(list_DB[0]);
						keys['X'] = 0;
					}
					if (keys['C'] && !player.WalkAnimation(CountLoop)) {
						battle = true;
						BattleTalk = 1;
						interrupt = true;
						arrow.SetObjects(9, 8);
						Map.Loading_Map(list_DB[0]);
						keys['C'] = 0;
					}
					// npc 말걸기
					else if (keys['Z'] && !player.WalkAnimation(CountLoop)) {
						// z 눌렀을때 앞이 NPC 인지 확인
						if (Map.Check_Map(player.x + (player.direct - 1) % 2, player.y + (player.direct - 2) % 2) == 5) {
							// 맞다면 누군지 탐색
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
								CountLoop = 0;
								Answer = -1;
							}
						}
						else TalkNPC = -1;
					}
					else {
						//방향키 입력 받으면 움직임
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