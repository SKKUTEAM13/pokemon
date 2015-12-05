#pragma once

#define START_X				30
#define START_Y				60
#define NUM_CHARACTER_IMAGE 46	// 캐릭터 이미지 갯수
#define NUM_MAP_IMAGE		10	// 맵 이미지 갯수
#define NUM_WINDOW_IMAGE	7	// 테두리 등 User interface 갯수
#define NUM_INTRO_IMAGE		6	// 
#define NUM_BGM				15
#define NUM_STORY			104
#define NUM_TOTAL_NPC		24
#define NUM_BATTLE_IMAGE	17

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

bool	intro = true;				// intro
bool	Talk = false;				// 대화 flag
bool	YesNo = false;				// YesNo flag
bool	interrupt = true;			// 외부 입력이 들어오거나 z키를 눌렀을때 반응하면 true
bool	IsJump = false;				// 
bool	battle = false;				// battle flag
bool	skill = false;				// 스킬 리스트 flag
bool	gameover = false;			// 게임에서 죽으면 센터 앞으로 리셋
bool	OK = false;					// 사용자가 글을 읽고 보내는 키입력

pokemap	Map;

// 데이터 //
// 배틀용 이미지 //
char path_back[1][63] = { { "image/battle/pika0.bmp" } };
char path_front[NUM_BATTLE_IMAGE][63] =
// 0 //
{ { "image/battle/gugu1.bmp" },
{ "image/battle/digda1.bmp" },

{ "image/battle/aboke1.bmp" },
{ "image/battle/yadon1.bmp" },
{ "image/battle/tanguri1.bmp" },
// 5 //
{ "image/battle/coil1.bmp" },
{ "image/battle/parasect1.bmp" },
{ "image/battle/dactrio1.bmp" },
{ "image/battle/ddogas1.bmp" },
{ "image/battle/nyaong1.bmp" },
{ "image/battle/jilpeok1.bmp" },
{ "image/battle/yungela1.bmp" },
{ "image/battle/dandanji1.bmp" },
{ "image/battle/majayong1.bmp" },
{ "image/battle/ddodogas1.bmp" },
{ "image/battle/yadoran1.bmp" },

{ "image/battle/phantom1.bmp" } };
// 10 //
// 15 //
// 캐릭터 //
char path_char[NUM_CHARACTER_IMAGE][63] =
// 0 //
{ { "image/object/Gi_U0.bmp" },				// 지우 LEFT
{ "image/object/Gi_U1.bmp" },				// 지우 UP
{ "image/object/Gi_U2.bmp" },				// 지우 RIGHT
{ "image/object/Gi_U3.bmp" },				// 지우 DOWN
{ "image/object/object_grass.bmp" },
// 5 //
{ "image/object/pikachu0.bmp" },		// 피카츄 5
{ "image/object/pikachu1.bmp" },
{ "image/object/pikachu2.bmp" },
{ "image/object/pikachu3.bmp" },
{ "image/object/nurse.bmp" },
// 10 //
{ "image/object/null.bmp" },			// 투명 10
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/shadow.bmp" },
// 15 //
{ "image/object/rocketM0.bmp" },		// 로켓남 15
{ "image/object/rocketM1.bmp" },
{ "image/object/rocketM2.bmp" },
{ "image/object/rocketM3.bmp" },
{ "image/object/yeesl0.bmp" },			// 이슬 19
// 20 //
{ "image/object/yeesl1.bmp" },
{ "image/object/yeesl2.bmp" },
{ "image/object/yeesl3.bmp" },
{ "image/object/zzz0.bmp" },			// 잠만보 23
{ "image/object/zzz1.bmp" },
// 25 //
{ "image/object/zzz2.bmp" },
{ "image/object/zzz3.bmp" },
{ "image/object/boss0.bmp" },			// 보스 27
{ "image/object/boss1.bmp" },
{ "image/object/boss2.bmp" },
// 30 //
{ "image/object/boss3.bmp" },
{ "image/object/rocketG0.bmp" },		// 로켓걸 31
{ "image/object/rocketG1.bmp" },
{ "image/object/rocketG2.bmp" },
{ "image/object/rocketG3.bmp" },
// 35 //
{ "image/object/ork0.bmp" },			// 오박사 35
{ "image/object/ork1.bmp" },
{ "image/object/ork2.bmp" },
{ "image/object/ork3.bmp" },
{ "image/object/mom0.bmp" },			// 엄마 39
// 40 //
{ "image/object/mom1.bmp" },
{ "image/object/mom2.bmp" },
{ "image/object/mom3.bmp" },
{ "image/object/taerok.bmp" },
{ "image/object/yunjeong.bmp" },
// 45 //
{ "image/object/dongmin.bmp" }
};
// 맵 //
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
int BGM_map[NUM_MAP_IMAGE] = { 1, 2, 3, 1, 4, 4, 1, 13, 13, 3};
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
{ "BGM/wild-defeated.mp3" },
{"BGM/pokemon-recovery.mp3"},
{ "BGM/trainer-intro-rocket.mp3"},
{"BGM/battle-rocket.mp3"},
{"BGM/dark-cave.mp3"},
{"BGM/ending-route-26.mp3"}
};
// 인트로 //
char path_intro[NUM_INTRO_IMAGE][63] =
{ { "image/intro/intro1.bmp" },
{ "image/intro/intro2.bmp" },
{ "image/intro/intro3.bmp" },
{ "image/intro/intro4.bmp" },
{ "image/intro/intro5.bmp" },
{ "image/intro/intro6.bmp" } };
// 폰트 //
char path_font[1][63] = { { "image/font/font.bmp" } };
// 윈도우 //
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
////////////////////// 맵 데이터 ////////////////
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
// 0 마을 //
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
// 1 센터 //
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
// 2 오박사 집 //
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1,
1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
1, 1, 0, 163925, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 153515, 1, 1, 0, 1,
1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
1, 1, 1, 0, 0, 3023, 3023, 0, 0, 0, 0, 0, 0, 1, 1 },
// 3 숲길1 //
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
// 4 얼음동굴 //
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
// 5 용암워프길 //
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700093, 0,
0, 0, 0, 0, 0, 0, 0, 502033, 0, 0, 0, 0, 0, 1, 0,
0, 0, 171535, 0, 0, 0, 507073, 1, 1, 511093, 0, 1, 1, 26, 191505,
0, 0, 6, 507023, 0, 0, 0, 0, 0, 0, 512073, 1, 1, 1, 1,
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 501093, 0, 0, 0, 0, 512053, 0, 0, 0, 511103, 1, 507063, 0,
0, 0, 0, 0, 0, 0, 183125, 16, 0, 0, 0, 0, 1, 0, 0,
0, 0, 0, 0, 0, 500093, 1, 1, 507023, 0, 0, 0, 1, 511033, 0,
506073, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 502043, 0, 0, 0, 0, 0, 0, 0, 508023, 1, 0, 0, 0,
413053, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 512053, 0, 0 },
// 6 숲길2 //
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
// 7 아지트1 //
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
0, 1, 803023, 1, 0, 0, 0, 0, 0, 0, 0, 1, 803083, 1, 0,
0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
0, 1, 0, 0, 0, 1, 807043, 1, 0, 0, 101525, 26, 0, 0, 0,
0, 6, 83105, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0,
0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0,
0, 1, 0, 0, 91525, 16, 0, 0, 0, 0, 0, 1, 813083, 1, 0,
0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0,
1, 1, 0, 0, 0, 0, 1, 813023, 1, 0, 0, 0, 0, 0, 0,
513013, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
// 8 아지트2 //
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 701023, 1, 1, 1, 1, 0, 0, 0, 1, 1, 706093, 1, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 1, 211525, 16, 705043, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 903053,26, 36, 1, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 2025, 122715, 113115, 1, 0, 1, 1, 1, 1, 0,
0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
0, 1, 711023, 1, 0, 0, 1, 1, 1, 1, 1, 1, 711073, 1, 0,
0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 9 엔딩 오박사 집 //
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
1, 1, 234305, 0, 0, 0, 224315, 0, 0, 0, 234415, 0, 0, 1, 1 } };
struct Story {
	int YesNext;
	int NoNext;
	int link;
	const char data[50];
};
// 0 끝나는 대화 1 이어지는 대화 4 치료   yes = no = 다음 대화
// 2 yes no 3 배틀	이기거나 선택 yes 지거나 no, 'x' 버튼이면 no
Story talk_poke[NUM_STORY] =
// 0 //
{ {0, 0, 0, "" },
// 피카츄
{ 1, 1, 0, "Pika?" },
{ -1, -1, 0, "Pikachu!" },
// 간호순
{ 1, 1, 1, "Welcome to POKEMON CENTER!" },
{ 1, 2, 2, "Need pokemon cure service?" },
// 5 //
{ 1, 1, 4, "The treatment is over!" },
{ -3, -3, 0, "Care for your pokemon well." },
{ 1, 0, 3, "We said you can't pass!" },
{ 0, 0, 0, "We don't know where she is." },
{ -1, 0, 3, "Hey, You can't pass here!"},
// 10 //
{ 37, 37, 1, "I can tell you where she is."},
{ 0, 0, 0, "Rigth Side of Ice Cave..." },
{ 0, 0, 0, "for sale : 3000 sqt Mart" },
{ 1, 1, 0, "...zzZ" },
{ -1, -1, 0, "zz..zz..Z" },
// 15 //
{ 1, 1, 1, "Oh, you woke up!" },
{ 32, 32, 1, "I'm sorry that we couldn't" },
{ 1,0,3, "intruder!" },
{ 1,1,1,"Damn it!.. But," },
{ -1,-1,0,"You can't defeat inner member" },
// 20 //
{ 1,0,3,"You cannot go any more!" },
{ 1,1,1, "Is she your girlfriend?" },
{ -1,-1,0, "I think It's weird..." },
{ 1,0,3,"I'm different from others!" },
{ 1,1,1,"Our Boss needs her." },
// 25 //
{ 1,1,1, "But I don't know why." },
{ 1,1,1, "I just know she is special." },
{ 1,1,1, "You can go inside now." },
{ -1,-1,0, "But it will be much hard. " },
{ 1, 1, 1, "You can save her." },
// 30 //
{ -1, -1, 0, "Hurry up!" },
{ 1, 1, 1, "Oh, you woke up my son?" },
{ 1, 1, 1, "?? What? girlfriend?" },
{ 1, 1, 1, "You might have a nice dream." },
{ 17, 17, 1, "But time to go to school~" },
// 35 //
{ 0, 0, 0, "1000 years old Tree" },
{ 1, 1, 1, "It's great that you get here." },
{ 21, 0, 3, "But it will be your limit! " },
{ 1, 1, 1, "What did other members do?" },
{ 21, 0, 3, "Alright, I'll test you!" },
// 40 //
{ 1, 1, 1, "If you save her" },
{ 1, 1, 1, "Give me Pikachu..." },
{ 1, -2, 3, "Or Fight!" },
{ 0, 0, 0, "go away." },
{ 1, 1, 1, "It's easy to get here," },
// 45 //
{ 1, -1, 3, "but you can't win easily!" },
{ 0, 0, 0, "No! I can't accept." },
{ -36,-36, 3, ".. If you defeat me!.." },
{ 1,1,1, "rescue your girlfriend." },
{ 1,1,1, "She was kidnapped by stranger." },
// 50 //
{ -1,-1,0, "Save her with your Pikachu!" },
{ -20,-20,0, "Hurry up not to be late!" },
{ 1,1,1, "? What? pokemon??" },
{ 1,1,1, "What are you talking about?" },
{ 1,1,1, "Anyway, my son," },
// 55 //
{ 1,1,1, "It'll soon be christmas!" },
{ 1,1,1, "Do you have any girlfriend " },
{ -3,-3,0, "to be with for christmas?" },
{ 1,1,1, "Ha, It's my limit." },
{ 0,0,0, "Maybe you can get boss's room" },
// 60 //
{ 1,1,1, "Ah, you're looking for her?" },
{ 1,1,1, "No one saw her face." },
{ 1,1,1, "Is she beautiful?" },
{ -3,-3,0, "Why don't you answer?" },
{ 1,1,1, "I'm the first guardian." },
// 65 //
{ 1,1,1, "If you defeat me," },
{ 1,1,1, "You can get to Boss's room." },
{ 1,0,3, "It's unavoidable fight!" },
{ 1,1,1, "Go to the Boss's room and" },
{ 1,1,1, "Defeat executives!" },
// 70 //
{ -2,-2,0, "Maybe you can find something." },
{ 1,1,1, "Wow, what a strong intruder." },
{ 1,1,1, "It's been so long," },
{ 1,1,1, "since I fought." },
{ 1,0,3, "OK, Plaese! Excite me!" },
// 75 //
{ 1,1,1, "Do you believe her?" },
{ 1,1,1, "I want to see your face" },
{ -2,-2,0, "when you meet her" },
{ 1,1,1, "Welcome to our laboratory!" },
{ 1,1,1, "For just a girl, you fight." },
// 80 //
{ 1,1,1, "What a beautiful scene!" },
{ 1,1,1, "But It's real not dream." },
{ 1,1,1, "You are not hero!" },
{ 1,0,3, "It's time to go home, kid!" },
{ 1,1,1, "I advise that.." },
// 85 //
{ 1,1,1, "It's better not to know" },
{ -2,-2,0, "Well, Consult with our Boss." },
{ 1,1,1, "Hello! I'm the boss you find." },
{ 1,1,1, "We need her because" },
{ 1,1,1, "She has much energy." },
// 90 //
{ 1,1,1, "and I found it derive from" },
{ 1,1,1, "just you strongly!" },
{ 1, 1, 1, "I don't know why!" },
{ 1, 1, 1, "I want to do research on you!" },
{ 1, 1, 1, "If you defeat me" },
// 95 //
{ 1,1,1, "You'll come to know all!" },
{ 1,0,3,"The finale is about to come!" },
{1,1,1, "She is what you dreamed of.."},
{-1,-1,0, "Go and get answer."},
{1,1,5," "},
// 100 //
{1,1,1, "Can you hear?"},
{1,1,1, "pika!"},
{1,1,1, "Thank you.. my boyfriend."},
{0,0,0, "- Thank You For Playing! -"}
};

int Scenario[NUM_TOTAL_NPC][3] =
{ { 0,0,0 },{ 1,0,0 },{ 3,0,0 },{ 7,6,4 },{ 9,10,4 },
{ 10, 5, 6 },{ 12, 0, 0 },{ 13, 0, 0 },{ 36, 16, 10 },{ 64, 11, 11 },
{ 38, 15, 10 },{ 78, 13, 12 },{ 87, 17, 13 },{ 31, 0, 0 },{ 52, 0, 0 },
{ 15, 0, 0 },{ 29, 0, 0 },{ 17, 3, 7 },{ 20, 9, 8 },{ 23, 14, 9 },
{ 35, 0, 0 },{ 71, 12, 12 },
//22
{ 99, 0, 0 },{ 103, 0, 0 }
};

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