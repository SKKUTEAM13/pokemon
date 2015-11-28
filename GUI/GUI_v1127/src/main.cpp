/*
*	Version 11.27
*	메뉴를 불러내면 화살표 객체를 만들고 맵에 화살표가 움직일 공간을 로딩해서 충돌나게 까지 만듬
*	나중에 z버튼 누르면 화살표 좌표(x, y)를 받아 이벤트가 발생하게 할 예정.
*	Animation and MAP
*	OpenGL, MAP, BMP
*
*/
#pragma comment(lib, "winmm.lib")

#include <stdio.h>			// Header File For Standard Input / Output
#include <gl/freeglut.h>	// Header File For OpenGL 
#include <mmsystem.h>

#include "map.h"
#include "object.h"
#include "SOIL.h"			// Header File For Loading BMP Image
#include "timer.h"

#define START_X 30			// Start Map point Left Top
#define START_Y 60
#define NUM_CHARACTER_IMAGE 5
#define NUM_MAP_IMAGE 9
#define NUM_WINDOW_IMAGE 4

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;	// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

							/* bool for window */
bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = true;		// Window Active Flag Set To ture By Default
bool	fullscreen = true;	// Fullscreen Flag Set To Fullscreen Mode By Default

int		loop1;				// Generic Loop1
int		loop2;				// Generic Loop2

//////////////////// 음악 재생 함수/////////////////
MCI_OPEN_PARMS      mciOpen; //음악 파일을 로드
MCI_PLAY_PARMS       mciPlay; //음악 파일을 재생
MCI_STATUS_PARMS   mciStatus; //음악 파일의 상태

DWORD BGM[20];
UINT wDeviceID = 0;

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
////////////////////////////////////////////////
char path_font[1][63] = { { "image/font/font.bmp" } };
char path_char[NUM_CHARACTER_IMAGE][63] =
{ { "image/object/Gi_U0.bmp" },				// 지우 LEFT
{ "image/object/Gi_U1.bmp" },				// 지우 UP
{ "image/object/Gi_U2.bmp" },				// 지우 RIGHT
{ "image/object/Gi_U3.bmp" },				// 지우 DOWN
{ "image/object/object_grass.bmp" } };		// 캐릭터 풀 애니메이션 

char path_map[NUM_MAP_IMAGE][63] =
{ { "image/map/icon.bmp" },
{ "image/map/senter.bmp" },
{ "image/map/home.bmp" },
{ "image/intro/intro1.bmp" },
{ "image/intro/intro2.bmp" },
{ "image/intro/intro3.bmp" },
{ "image/intro/intro4.bmp" },
{ "image/intro/intro5.bmp" },
{ "image/intro/intro6.bmp" } };

char path_window[NUM_WINDOW_IMAGE][63] =
{ { "image/window/menu.bmp" },
{ "image/window/talk.bmp" },
{ "image/window/yesno.bmp" },
{ "image/window/battle.bmp" } };

int list_DB[1][165] =
{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int map_DB[NUM_MAP_IMAGE][165] =
{ { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 206093, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
0, 0, 0, 1, 0, 0, 0, 0, 105093, 0, 0, 0, 1, 0, 0,
0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1,
1, 1, 0, 0, 8053, 8053, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
1, 1, 1, 0, 0, 3023, 3023, 0, 0, 0, 0, 0, 0, 1, 1 },
{},
{},
{},
{} };

/* Texture */
GLuint	texture_char[NUM_CHARACTER_IMAGE];			// 캐릭터 이미지 저장
GLuint	texture_map[NUM_MAP_IMAGE];					// 맵 이미지 저장
GLuint	texture_window[NUM_WINDOW_IMAGE];
GLuint	texture_font[1];
GLuint	base;

int		adjust = 0;									// 속도 조절
int		steps[6] = { 1, 2, 4, 5, 10, 20 };			// 한번에 실행할 픽셀 수 조절. adjust로 정함.
int		count = LENGTH;
int		animation = 0;
int		isMenuOn = 0;								// 메뉴의 켜고 끔을 위해서 필요!

bool	intro = true;
bool	wait = true;
bool	interrupt = true;									// 외부 입력이 들어오거나 z키를 눌렀을때 반응하면 true

/* Unit In Game */
object	player;										// 플레이어 선언
map		Map;
timer	Timer;

/* 화살표, 화살표 움직일 맵 */
object	arrow;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

bool RegisterTextures(GLuint *texture, int NUM_IMAGE, char (*path)[63])
{
	for (loop1 = 0; loop1 < NUM_IMAGE; loop1++)
	{
		texture[loop1] = SOIL_load_OGL_texture
			(
				path[loop1],
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y
				);
		if (texture[loop1] == 0)
			return false;
		glBindTexture(GL_TEXTURE_2D, texture[loop1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

int LoadGLTextures()										// Load Bitmaps And Convert To Textures
{
	bool check = true;
	// 폰트
	check = check & RegisterTextures(texture_font, 1, path_font);

	// 캐릭터
	check = check & RegisterTextures(texture_char, NUM_CHARACTER_IMAGE, path_char);

	// map
	check = check & RegisterTextures(texture_map, NUM_MAP_IMAGE, path_map);

	// window
	check = check & RegisterTextures(texture_window, NUM_WINDOW_IMAGE, path_window);

	return true;
}

GLvoid BuildFont(GLvoid)									// Build Our Font Display List
{
	base = glGenLists(256);									// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, texture_font[0]);			// Select Our Font Texture
	for (loop1 = 0; loop1<256; loop1++)						// Loop Through All 256 Lists
	{
		float cx = float(loop1 % 16) / 16.0f;				// X Position Of Current Character
		float cy = float(loop1 / 16) / 16.0f;				// Y Position Of Current Character

		glNewList(base + loop1, GL_COMPILE);				// Start Building A List
		glBegin(GL_QUADS);									// Use A Quad For Each Character
		glTexCoord2f(cx, 1.0f - cy - 0.0625f);				// Texture Coord (Bottom Left)
		glVertex2d(0, 16);									// Vertex Coord (Bottom Left)
		glTexCoord2f(cx + 0.0625f, 1.0f - cy - 0.0625f);	// Texture Coord (Bottom Right)
		glVertex2i(16, 16);									// Vertex Coord (Bottom Right)
		glTexCoord2f(cx + 0.0625f, 1.0f - cy);				// Texture Coord (Top Right)
		glVertex2i(16, 0);									// Vertex Coord (Top Right)
		glTexCoord2f(cx, 1.0f - cy);						// Texture Coord (Top Left)
		glVertex2i(0, 0);									// Vertex Coord (Top Left)
		glEnd();											// Done Building Our Quad (Character)
		glTranslated(15, 0, 0);								// Move To The Right Of The Character
		glEndList();										// Done Building The Display List
	}														// Loop Until All 256 Are Built
}

GLvoid KillFont(GLvoid)										// Delete The Font From Memory
{
	glDeleteLists(base, 256);								// Delete All 256 Display Lists
}

GLvoid glPrint(GLint x, GLint y, int set, const char *fmt, ...)	// Where The Printing Happens
{
	char		text[256];									// Holds Our String
	va_list		ap;											// Pointer To List Of Arguments

	if (fmt == NULL)										// If There's No Text
		return;												// Do Nothing

	va_start(ap, fmt);										// Parses The String For Variables
	vsprintf_s(text, fmt, ap);								// And Converts Symbols To Actual Numbers
	va_end(ap);												// Results Are Stored In Text

	glEnable(GL_TEXTURE_2D);								// Enable Texture Mapping
	glLoadIdentity();										// Reset The Modelview Matrix
	glTranslated(x, y, 0);									// Position The Text (0,0 - Bottom Left)
	glListBase(base - 32 + (128 * set));					// Choose The Font Set (0 or 1)

	glScalef(1.2f, 1.2f, 1.0f);

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);		// Write The Text To The Screen
	glDisable(GL_TEXTURE_2D);								// Disable Texture Mapping
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)									// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
														// Calculate The Aspect Ratio Of The Window
	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);	// Create Ortho 640x480 View (0,0 At Top Left)

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine
	{
		return false;									// If Texture Didn't Load Return
	}

	BuildFont();										// Build The Font

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Backgroud
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing			
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Really Nice Perspective Calculations
	return true;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	// map
	glLoadIdentity();													
	glEnable(GL_TEXTURE_2D);																	
	glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, texture_map[Map.map_number]);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex2d( LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2d( LENGTH * (VERTICLE_LINE + 1) / 2,  LENGTH * (HORIZONTAL_LINE + 1) / 2);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2,  LENGTH * (HORIZONTAL_LINE + 1) / 2);
	glEnd();

	// player
	glLoadIdentity();
	//glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
	glTranslatef(player.fx + START_X * 1.0f, player.fy - 0.25 * LENGTH + START_Y * 1.0f, 0.0f);	// Move To The Fine Player Position


	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture(GL_TEXTURE_2D, texture_char[player.direct]);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((player.animation + 0) / 3.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);	// Top Left Of Player
	glTexCoord2f((player.animation + 1) / 3.0f, 0.99f); glVertex2d( LENGTH / 2.0, -LENGTH / 2.0);	// Top Right Of Player
	glTexCoord2f((player.animation + 1) / 3.0f, 0.50f); glVertex2d( LENGTH / 2.0,  LENGTH / 2.0);	// Bottom Right Of Player
	glTexCoord2f((player.animation + 0) / 3.0f, 0.50f); glVertex2d(-LENGTH / 2.0,  LENGTH / 2.0);	// Bottom Left Of Player
	glEnd();

	glBlendFunc(GL_ONE, GL_ONE);

	glBegin(GL_QUADS);																				// Start Drawing Our Player
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((player.animation + 0) / 3.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);	// Top Left Of Player
	glTexCoord2f((player.animation + 1) / 3.0f, 0.49f); glVertex2d( LENGTH / 2.0, -LENGTH / 2.0);	// Top Right Of Player
	glTexCoord2f((player.animation + 1) / 3.0f, 0.0f );	glVertex2d( LENGTH / 2.0,  LENGTH / 2.0);	// Bottom Right Of Player
	glTexCoord2f((player.animation + 0) / 3.0f, 0.0f );	glVertex2d(-LENGTH / 2.0,  LENGTH / 2.0);	// Bottom Left Of Player
	glEnd();																						// Done Drawing The Player

	if (player.tile == 1)
	{
		glLoadIdentity();
		//glTranslatef(7 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
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
		interrupt = true;
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(7 * LENGTH + START_X * 1.0f, 9 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d( LENGTH * (VERTICLE_LINE + 1) / 2, -LENGTH * 3 / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d( LENGTH * (VERTICLE_LINE + 1) / 2,  LENGTH * 3 / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * (VERTICLE_LINE + 1) / 2,  LENGTH * 3 / 2);
		glEnd();

		glLoadIdentity();
		glTranslatef(12.5 * LENGTH + START_X * 1.0f, 5 * LENGTH + START_Y * 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, texture_window[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * 4 / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2d( LENGTH * 4 / 2, -LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2d( LENGTH * 4 / 2,  LENGTH * (HORIZONTAL_LINE + 1) / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * 4 / 2,  LENGTH * (HORIZONTAL_LINE + 1) / 2);
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
		glDisable(GL_TEXTURE_2D);

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
		// 배틀
		glPrint(9.5 * LENGTH + START_X * 1.0f,
			8.5 * LENGTH + START_Y * 1.0f, 1,
			"FIGHT  $&");
		glPrint(9.5 * LENGTH + START_X * 1.0f,
			9.5 * LENGTH + START_Y * 1.0f, 0,
			"PACK   RUN");
		glDisable(GL_BLEND);
	}
	return true;
}

GLvoid KillGLWindow(GLvoid) 							// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(true);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Haver A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))				// Are We able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;									// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;								// Set hInstance To NULL
	}
	KillFont();												// Kill The Font We Built
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style

	fullscreen = fullscreenflag;		// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;						// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name


	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;									// Return FALSE
			}
		}
	}

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;							// Window Extended Style
		dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ShowCursor(false);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
	}

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,						// Extended Style For The Window
		"OpenGL",						// Class Name
		title,							// Window Title
		dwStyle |						// Defined Window Style
		WS_CLIPSIBLINGS |				// Required Window Style
		WS_CLIPCHILDREN,				// Required Window Style
		0, 0,							// Window Position
		width, height,
		NULL,							// No Parent Window
		NULL,							// No Menu
		hInstance,						// Instance
		NULL)))							// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))						// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))	// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	return true;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,				// Handle For This Window
	UINT	uMsg,				// Message For This Window
	WPARAM	wParam,				// Additional Message Information
	LPARAM	lParam)				// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_TIMER:
		KillTimer(hWnd, 1);
	case WM_ACTIVATE:								// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))						// Check Minimization State
		{
			active = true;							// Program Is Active
		}
		else
		{
			active = false;							// Program Is No Longer Active
		}

		return 0;									// Return To The Message Loop
	}

	case WM_SYSCOMMAND:								// Intercept System Commands
	{
		switch (wParam)								// Check System Calls
		{
		case SC_SCREENSAVE:							// Screensaver Trying To Start?
		case SC_MONITORPOWER:						// Monitor Trying To Enter Powersave?
			return 0;								// Prevent From Happening
		}
		break;										// Exit
	}

	case WM_CLOSE:									// Did We Receive A Close Message?
	{
		PostQuitMessage(0);							// Send A Quit Message
		return 0;									// Jump Back
	}

	case WM_KEYDOWN:								// Is A Key Being Held Down?
	{
		keys[wParam] = true;						// If So, Mark It As TRUE
		return 0;									// Jump Back
	}

	case WM_KEYUP:									// Has A Key Been Released?
	{
		keys[wParam] = false;						// If So, Mark It As FALSE
		return 0;									// Jump Back
	}

	case WM_SIZE:									// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));	// LoWord=Width, HiWord=Height
		return 0;									// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void object::MovementByKeyInput(int VK_INPUT)
{
	// VK	  ( LEFT : 37, UP : 38, RIGHT : 39, DOWN : 40 )
	// Direct ( LEFT :  0, UP :  1, RIGHT :  2, DOWN :  3 )
	
	if (keys[VK_INPUT]) 
	{
		int DirectKey = VK_INPUT - VK_LEFT;
		if (!Check_Direct(DirectKey)) {}
		else if ((count >= LENGTH) &&													// 애니메이션 한동작이 끝났는가
				(y <= HORIZONTAL_LINE) &&												// 맵 범위 x가 0~14, y가 0~10인지 확인 
				(x <= VERTICLE_LINE) && 
				(y >= 0) && (x >= 0) && 
				(Map.Check_Map(x + (DirectKey - 1) % 2, y + (DirectKey - 2) % 2) != 0)) // 맵이 충돌 타일인지 아닌지 검사
		{
			x += (DirectKey - 1) % 2;
			y += (DirectKey - 2) % 2;
			count = 0;
			// 잔디 타일에 들어가면 캐릭터한테 잔디 애니메이션 추가
			if (Map.Check_Map(x, y) == 2)
			{
				tile = 1;
			}
			else { tile = 0; }
			// 4번 타일은 미끄러지는 타일
			while (Map.Check_Map(x, y) == 4)
			{
				x += (DirectKey - 1) % 2;
				y += (DirectKey - 2) % 2;
			}
		}
		else if (count >= LENGTH) { count = 0; }
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
	
	player.Init(20, 20);
	Timer = Timer.TimerInit();

	BGM[0] = LoadMP3(hWnd, "BGM/GoldenCity.mp3");
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

			while (Timer.TimerGetTime() < start + float(steps[adjust] * 3.0f)) {}	// Waste Cycles On Fast Systems

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
					// 인트로로 인한 게임 정지
					if (intro)
					{
						if (wait) {
							count = 0;
							wait = false;
						}
						Map.map_number = 3 + animation;
						// 추가 입력 받으면 게임 시작
						if (count > LENGTH && keys['Z'])
						{
							interrupt = false;
							intro = false;

							// 게임 셋팅
							Map.Loading_Map(map_DB[0]);
							player.SetObjects(3, 2);
							Map.map_number = 0;
							animation = 0;
							count = LENGTH;
						}
						if (count % 40 == 0)
						{
							animation++;
							animation = animation % 6;
						}
						count++;
					}
					// 메뉴 켜서 게임 정지
					if (isMenuOn)
					{
						if (keys['X']) {
							isMenuOn = !isMenuOn;
							if (isMenuOn == 0)
								interrupt = false;
							Map.Loading_Map(map_DB[Map.map_number]);
							Timer.SleepTime(steps[adjust], 200);
						}
						else
						{
							arrow.MovementByKeyInput(VK_LEFT);
							arrow.MovementByKeyInput(VK_UP);
							arrow.MovementByKeyInput(VK_RIGHT);
							arrow.MovementByKeyInput(VK_DOWN);
							arrow.SetObjects(arrow.x, arrow.y);
							count++;
						}
					}
				}
				else {
					// 멈춰있을때 메뉴 부름
					if (keys['X'] && !player.WalkAnimation(count)) {
						isMenuOn = !isMenuOn;
						arrow.SetObjects(9, 8);
						Map.Loading_Map(list_DB[0]);
						Timer.SleepTime(steps[adjust], 200);
					}
					//방향키 입력 받으면 움직임
					player.MovementByKeyInput(VK_LEFT);
					player.MovementByKeyInput(VK_UP);
					player.MovementByKeyInput(VK_RIGHT);
					player.MovementByKeyInput(VK_DOWN);

					if (count < LENGTH)
					{
						player.WalkAnimation(count);
						count += steps[adjust];
					}
					// Move player from (fx, fy) to (x, y)
					player.MoveObject(steps[adjust]);

					if (Map.Check_Map(player.x, player.y) == 3)
					{
						Map.Link_Map(&(player.x), &(player.y));
						Map.Loading_Map(map_DB[Map.map_number]);
						player.SetObjects(player.x, player.y);
						count = 0;
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