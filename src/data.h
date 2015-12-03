#pragma once

#define START_X				30
#define START_Y				60
#define NUM_CHARACTER_IMAGE 46	// ĳ���� �̹��� ����
#define NUM_MAP_IMAGE		10	// �� �̹��� ����
#define NUM_WINDOW_IMAGE	7	// �׵θ� �� User interface ����
#define NUM_INTRO_IMAGE		6	// 
#define NUM_BGM				10
#define NUM_STORY			36
#define NUM_TOTAL_NPC		23
#define NUM_BATTLE_IMAGE	17

int		adjust = 0;									// �ӵ� ����
int		steps[6] = { 1, 2, 4, 5, 10, 20 };			// �ѹ��� ������ �ȼ� �� ����. adjust�� ����.
int		CountLoop = LENGTH;
int		animation = 0;								// people Ŭ������ �ƴ� �ƴ� �͵� �ִϸ��̼� ��
int		isMenuOn = 0;								// �޴��� �Ѱ� ���� ���ؼ� �ʿ�!
int		TalkNPC = -1;
int 	wait = 0;
int		Answer = -1;
int		X_Answer, Y_Answer;
int		BattleTalk = 0;
int		RamdomSkill;

bool	intro = true;				// intro
bool	Talk = false;				// ��ȭ flag
bool	YesNo = false;				// YesNo flag
bool	interrupt = true;			// �ܺ� �Է��� �����ų� zŰ�� �������� �����ϸ� true
bool	IsJump = false;				// 
bool	battle = false;				// battle flag
bool	skill = false;				// ��ų ����Ʈ flag
bool	gameover = false;			// ���ӿ��� ������ ���� ������ ����
bool	OK = false;					// ����ڰ� ���� �а� ������ Ű�Է�

pokemap	Map;

// ������ //
// ��Ʋ�� �̹��� //
char path_back[1][63] = { { "image/battle/pika0.bmp" } };
char path_front[NUM_BATTLE_IMAGE][63] = 
// 0 //
{ { "image/battle/gugu1.bmp" },
{ "image/battle/aboke1.bmp" },
{ "image/battle/nyaong1.bmp" },
{ "image/battle/ddogas1.bmp" },
{ "image/battle/jilpeok1.bmp" },
// 5 //
{ "image/battle/coil1.bmp" },
{ "image/battle/digda1.bmp" },
{ "image/battle/tanguri1.bmp" },
{ "image/battle/phantom1.bmp" },
{ "image/battle/yungela1.bmp" },
// 10 //
{ "image/battle/parasect1.bmp" },
{ "image/battle/dandanji1.bmp" },
{ "image/battle/majayong1.bmp" },
{ "image/battle/ddodogas1.bmp" },
{ "image/battle/dactrio1.bmp" },
// 15 //
{ "image/battle/yadon1.bmp" },
{ "image/battle/yadoran1.bmp"} };
// ĳ���� //
char path_char[NUM_CHARACTER_IMAGE][63] =
// 0 //
{ { "image/object/Gi_U0.bmp" },				// ���� LEFT
{ "image/object/Gi_U1.bmp" },				// ���� UP
{ "image/object/Gi_U2.bmp" },				// ���� RIGHT
{ "image/object/Gi_U3.bmp" },				// ���� DOWN
{ "image/object/object_grass.bmp" },
// 5 //
{ "image/object/pikachu0.bmp" },		// ��ī�� 5
{ "image/object/pikachu1.bmp" },
{ "image/object/pikachu2.bmp" },
{ "image/object/pikachu3.bmp" },
{ "image/object/nurse.bmp" },
// 10 //
{ "image/object/null.bmp" },			// ���� 10
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/shadow.bmp" },
// 15 //
{ "image/object/rocketM0.bmp" },		// ���ϳ� 15
{ "image/object/rocketM1.bmp" },
{ "image/object/rocketM2.bmp" },
{ "image/object/rocketM3.bmp" },
{ "image/object/yeesl0.bmp" },			// �̽� 19
// 20 //
{ "image/object/yeesl1.bmp" },
{ "image/object/yeesl2.bmp" },
{ "image/object/yeesl3.bmp" },
{ "image/object/zzz0.bmp" },			// �Ḹ�� 23
{ "image/object/zzz1.bmp" },
// 25 //
{ "image/object/zzz2.bmp" },
{ "image/object/zzz3.bmp" },
{ "image/object/boss0.bmp" },			// ���� 27
{ "image/object/boss1.bmp" },
{ "image/object/boss2.bmp" },
// 30 //
{ "image/object/boss3.bmp" },
{ "image/object/rocketG0.bmp" },		// ���ϰ� 31
{ "image/object/rocketG1.bmp" },
{ "image/object/rocketG2.bmp" },
{ "image/object/rocketG3.bmp" },
// 35 //
{ "image/object/ork0.bmp" },			// ���ڻ� 35
{ "image/object/ork1.bmp" },
{ "image/object/ork2.bmp" },
{ "image/object/ork3.bmp" },
{ "image/object/mom0.bmp" },			// ���� 39
// 40 //
{ "image/object/mom1.bmp" },
{ "image/object/mom2.bmp" },
{ "image/object/mom3.bmp" },
{ "image/object/taerok.bmp" },
{ "image/object/yunjeong.bmp" },
// 45 //
{ "image/object/dongmin.bmp" }
};
// �� //
char path_map[NUM_MAP_IMAGE][63] =
{ { "image/map/icon.bmp" },
{ "image/map/senter.bmp" },
{ "image/map/home.bmp" },
{ "image/map/forrest.bmp" },
{ "image/map/icecave.bmp" },
{ "image/map/rocket1.bmp" },
{ "image/map/forrest2.bmp" },
{ "image/map/AGIT_1-3.bmp" },
{ "image/map/AGIT_2-4.bmp" },
{ "image/map/endinghome.bmp"} };
int BGM_map[NUM_MAP_IMAGE] = { 1, 2, 3, 1, 4, 4, 1 };
// BGM //
char path_BGM[NUM_BGM][100] =
{ { "BGM/title-screen.mp3" },
{ "BGM/welcome-to-the-world-of-pokemon.mp3" },
{ "BGM/pokemon-center.mp3" },
{ "BGM/pokemon-lab.mp3" },
{ "BGM/cave.mp3" },
{ "BGM/trainer-battle-theme.mp3"},
{ "BGM/trainer-defeated.mp3"},
{ "BGM/slash.mp3"},
{ "BGM/wild-battle-theme.mp3" },
{ "BGM/wild-defeated.mp3" }
};
// ��Ʈ�� //
char path_intro[NUM_INTRO_IMAGE][63] =
{ { "image/intro/intro1.bmp" },
{ "image/intro/intro2.bmp" },
{ "image/intro/intro3.bmp" },
{ "image/intro/intro4.bmp" },
{ "image/intro/intro5.bmp" },
{ "image/intro/intro6.bmp" } };
// ��Ʈ //
char path_font[1][63] = { { "image/font/font.bmp" } };
// ������ //
char path_window[NUM_WINDOW_IMAGE][63] =
// 0 //
{ { "image/window/menu.bmp" },
{ "image/window/talk.bmp" },
{ "image/window/yesno.bmp" },
{ "image/window/battle.bmp" },
{ "image/window/skill.bmp"},
// 5 //
{ "image/window/pokestats.bmp"},
{ "image/window/animystats.bmp"} };
////////////////////// �� ������ ////////////////
int list_DB[1][165] =
{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 4, 4, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int map_DB[NUM_MAP_IMAGE][165] =
// 0 ���� //
{ { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 206093, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
0, 34, 34, 1, 34, 34, 0, 0, 105093, 0, 0, 0, 61035, 0, 0,
0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301053,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301063,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301073,
0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 10505, 1, 1, 1, 301083,
0, 0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 301093,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
// 1 ���� //
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1,
1, 1, 1, 1, 1, 905, 1, 0, 1, 1, 1, 0, 0, 1, 1,
1, 0, 0, 0, 0, 21005, 0, 0, 1, 1, 1, 1, 0, 1, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1,
1, 1, 0, 0, 0, 8053, 8053, 0, 0, 0, 0, 0, 1, 1, 1 },
// 2 ���ڻ� �� //
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 0, 183925, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 193515, 1, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
1, 1, 1, 0, 0, 3023, 3023, 0, 0, 0, 0, 0, 0, 1, 1 },
// 3 ����1 //
{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
1, 0, 1, 0, 1, 0, 0, 0, 401093, 0, 1, 1, 1, 1, 1,
0, 1, 44, 1, 201005, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,
0, 1, 0, 1, 0, 0, 1, 1, 16, 33105, 0, 0, 0, 1, 1,
13053, 1, 1, 1, 1, 1, 1, 1, 26, 41505, 0, 0, 0, 0, 0,
13063, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
13073, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 72305, 72405,
13083, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 72605, 72505,
13093, 1, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
// 4 �������� //
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 0,
0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0,
0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 0, 4, 0,
0, 4, 0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0,
0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0, 1, 501103,
0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
0, 308033, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 606053, 0, 0 },
// 5 ��Ͽ����� //
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700093, 0,
0, 0, 0, 0, 0, 0, 0, 502033, 0, 0, 0, 0, 0, 1, 0,
0, 0, 171535, 0, 0, 0, 507073, 1, 1, 511093, 0, 1, 1, 16, 191505,
0, 0, 6, 507023, 0, 0, 0, 0, 0, 0, 512073, 1, 1, 1, 1,
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 501093, 0, 0, 0, 0, 512053, 0, 0, 0, 511103, 1, 507063, 0,
0, 0, 0, 0, 0, 0, 183125, 26, 0, 0, 0, 0, 1, 0, 0,
0, 0, 0, 0, 0, 500093, 1, 1, 507023, 0, 0, 0, 1, 511033, 0,
506073, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 502043, 0, 0, 0, 0, 0, 0, 0, 508023, 1, 0, 0, 0,
413053, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 512053, 0, 0 },
// 6 ����2 //
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 51525,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
0, 0, 0, 0, 0, 0, 412093, 0, 0, 1, 1, 1, 0, 0, 0,
0, 0, 2, 2, 2, 2, 1, 1, 24, 1, 0, 1, 1, 0, 0,
0, 0, 2, 2, 2, 2, 1, 1, 24, 1, 1, 1, 1, 0, 0,
0, 0, 1, 34, 34, 34, 34, 34, 0, 1, 1, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
// 7 ����Ʈ1 //
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
0, 1, 803023, 1, 0, 0, 0, 0, 0, 0, 0, 1, 803083, 1, 0,
0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
0, 1, 0, 0, 0, 1, 807043, 1, 0, 0, 1525, 1, 0, 0, 0,
0, 1, 1505, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0,
0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0,
0, 1, 0, 0, 1525, 1, 0, 0, 0, 0, 0, 1, 813083, 1, 0,
0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0,
1, 1, 0, 0, 0, 0, 1, 813023, 1, 0, 0, 0, 0, 0, 0,
513013, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
// 8 ����Ʈ2 //
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 701023, 1, 1, 1, 1, 0, 0, 0, 1, 1, 706093, 1, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 1, 0, 1, 705043, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 911033,1, 1, 1, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 2025, 1515, 1515, 1, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 711023, 1, 0, 0, 1, 1, 1, 1, 1, 1, 711073, 1, 0,
0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 9 ���� ���ڻ� �� //
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 0, 133925, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 143515, 1, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
1, 1, 4305, 0, 0, 0, 4315, 0, 0, 0, 4415, 0, 0, 1, 1 } };
struct Story {
	int YesNext;
	int NoNext;
	int link;
	const char data[30];
};
// 0 ������ ��ȭ 1 �̾����� ��ȭ 4 ġ��   yes = no = ���� ��ȭ
// 2 yes no 3 ��Ʋ	�̱�ų� ���� yes ���ų� no, 'x' ��ư�̸� no
Story talk_poke[NUM_STORY] =
// 0 //
{ {0, 0, 0, "" },
// ��ī��
{ 1, 1, 0, "Pika?" },
{ -1, -1, 0, "Pikachu!" },
// ��ȣ��
{ 1, 1, 1, "Welcome to CENTER!" },
{ 1, 2, 2, "back to perfect!" },
// 5 //
{ 1, 1, 4, "health." },
{ -4, -4, 0, "see you again" },
{ 1, 0, 3, "Get out Here!" },
{ 0, 0, 0, "Sorry..." },
{ -1, 0, 3, "I'm Ace in Team Rocket!"},
// 10 //
{ 1, 0, 3, "I know where she is."},
{ 0, 0, 0, "Rigth Side of Ice Cave..."},
{ 0, 0, 0, "for sale : 3000 sqt Mart"},
{ 1, 1, 0, "...zzZ" },
{ -1, -1, 0, "zz..zz..Z" },
// 15 //
{1, 1, 0, "Team Rocket kidnap her!"},
{-1, -1, 0, "Harry up!"},
{ 1,0,3, "Invader!" },
{ 1,1,1,"Damn it!.. But," },
{ 0,0,0,"You can't defeat inner member" },
// 20 //
{ 1,0,3,"You cannot go any more!" },
{ 1,1,1, "Is she your girlfriend?" } ,
{ -1,-1,0, "I think It's weird..." },
{ 1,0,3,"I'm different from others!" },
{ 1,1,1,"Our Boss needs her." },
// 25 //
{ 1,1,1, "But I don't know why." },
{ 1,1,1, "I just know she is special." },
{ 1,1,1, "You can go inside now." },
{ -1,-1,0, "But it will be much hard. " },
{1, 1, 0, "You can save her."},
// 30 //
{-1, -1, 0, "I have important work..."},
{1, 1, 1, "How was the game?"},
{1, 1, 1, "I make for you"},
{0, 0, 0, "You wil make girl friend"},
{-1, -1, 0, "Cheer up!"},
// 35 //
{0, 0, 0, "1000 years old Tree"} };
int Scenario[NUM_TOTAL_NPC][3] = 
{ {0,0,0}, {1,0,0}, {3,0,0}, {7,1,2}, {9,3,1}, 
{10, 4, 4}, {12, 0, 0}, {13, 0, 0}, {}, {},
{}, {}, {}, {34, 0, 0}, {31, 0, 0},
{15, 0, 0}, {28, 0, 0}, { 17, 6, 1 },{ 20, 8, 1 },{ 23, 10, 1 },
{35, 0, 0} };

////////////////////////////

class NPCHandler
{
public:
	int GetYesNext();
	int GetNoNext();
	int GetLink();
	int GetSelect();
	int GetLevel();
	const char *GetData();
	void SetYesNext();
	void SetNoNext();
	void SetDeletePoke();
};

int NPCHandler::GetYesNext() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].YesNext; }
int NPCHandler::GetNoNext() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].NoNext; }
int NPCHandler::GetLink() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].link; }
int NPCHandler::GetSelect() { return Scenario[(Map.NPC[TalkNPC].story)][1]; }
int NPCHandler::GetLevel() { return Scenario[(Map.NPC[TalkNPC].story)][2]; }
const char *NPCHandler::GetData() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].data; }
void NPCHandler::SetYesNext() { Scenario[(Map.NPC[TalkNPC].story)][0] += GetYesNext(); }
void NPCHandler::SetNoNext() { Scenario[(Map.NPC[TalkNPC].story)][0] += GetNoNext(); }
void NPCHandler::SetDeletePoke() { Scenario[(Map.NPC[TalkNPC].story)][1] = 0; }