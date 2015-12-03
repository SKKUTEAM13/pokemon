#pragma once

#define START_X				30
#define START_Y				60
#define NUM_CHARACTER_IMAGE 23	// 캐릭터 이미지 갯수
#define NUM_MAP_IMAGE		7	// 맵 이미지 갯수
#define NUM_WINDOW_IMAGE	7	// 테두리 등 User interface 갯수
#define NUM_INTRO_IMAGE		6	// 
#define NUM_BGM				7
#define NUM_STORY			12
#define NUM_TOTAL_NPC		6
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
// 캐릭터 //
char path_char[NUM_CHARACTER_IMAGE][63] =
// 0 //
{ { "image/object/Gi_U0.bmp" },				// 지우 LEFT
{ "image/object/Gi_U1.bmp" },				// 지우 UP
{ "image/object/Gi_U2.bmp" },				// 지우 RIGHT
{ "image/object/Gi_U3.bmp" },				// 지우 DOWN
{ "image/object/object_grass.bmp" },
// 5 //
{ "image/object/pikachu0.bmp" },
{ "image/object/pikachu1.bmp" },
{ "image/object/pikachu2.bmp" },
{ "image/object/pikachu3.bmp" },
{ "image/object/nurse.bmp" },
// 10 //
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
{ "image/object/null.bmp" },
("image/object/shadow.bmp"),
// 15 //
{ "image/object/rocketM0.bmp" },
{ "image/object/rocketM1.bmp" },
{ "image/object/rocketM2.bmp" },
{ "image/object/rocketM3.bmp" },
{ "image/object/yeesl0.bmp" },
// 20 //
{ "image/object/yeesl1.bmp" },
{ "image/object/yeesl2.bmp" },
{ "image/object/yeesl3.bmp" } };
// 맵 //
char path_map[NUM_MAP_IMAGE][63] =
{ { "image/map/icon.bmp" },
{ "image/map/senter.bmp" },
{ "image/map/home.bmp" },
{ "image/map/forrest.bmp" },
{ "image/map/icecave.bmp" },
{ "image/map/rocket1.bmp" },
{ "image/map/forrest2.bmp" } };
int BGM_map[NUM_MAP_IMAGE] = { 1, 2, 3, 1, 4, 4, 1 };
// BGM //
char path_BGM[NUM_BGM][100] =
{ { "BGM/title-screen.mp3" },
{ "BGM/welcome-to-the-world-of-pokemon.mp3" },
{ "BGM/pokemon-center.mp3" },
{ "BGM/pokemon-lab.mp3" },
{ "BGM/cave.mp3" },
{ "BGM/trainer-battle-theme.mp3"},
{ "BGM/trainer-defeated.mp3"} };
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
{ { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 0, 206093, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
0, 34, 34, 1, 34, 34, 0, 0, 105093, 0, 0, 0, 1, 0, 0,
0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301053,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301063,
0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 301073,
0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 10505, 1, 1, 1, 301083,
0, 0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 301093,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
1, 0, 1, 0, 1, 0, 0, 0, 401093, 0, 1, 1, 1, 1, 1,
0, 1, 44, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1,
0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1,
13053, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
13063, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
13073, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 36, 31505,
13083, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 46, 41505,
13093, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
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
0, 308033, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 606043, 0, 0 },
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
0, 0, 0, 0, 0, 0, 0, 502033, 0, 0, 0, 0, 0, 1, 0,
0, 0, 1, 0, 0, 0, 507073, 1, 1, 511093, 0, 1, 1, 1, 1,
0, 0, 1, 507023, 0, 0, 0, 0, 0, 0, 512073, 1, 1, 1, 1,
0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 501093, 0, 0, 0, 0, 512053, 0, 0, 0, 511103, 1, 507063, 0,
0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0,
0, 0, 0, 0, 0, 500093, 1, 1, 507023, 0, 0, 0, 1, 511033, 0,
506073, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 502043, 0, 0, 0, 0, 0, 0, 0, 508023, 1, 0, 0, 0,
413053, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 512053, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 56, 51505,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
0, 0, 0, 0, 0, 0, 412093, 0, 0, 1, 1, 1, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 24, 1, 0, 1, 1, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 24, 1, 1, 1, 1, 0, 0,
0, 0, 1, 34, 34, 34, 34, 34, 0, 1, 1, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

struct Story {
	int YesNext;
	int NoNext;
	int link;
	const char data[30];
};

Story talk_poke[NUM_STORY] =
// 0 //
{ {0, 0, 0, "" },
{ 2, 2, 0, "Pika?" },
{ 1, 1, 0, "Pikachu!" },
{ 4, 4, 1, "Welcome to CENTER!" },
{ 5, 6, 2, "back to perfect!" },
// 5 //
{ 6, 6, 4, "health." },
{ 3, 3, 0, "see you again" },
{ 8, 7, 3, "Get out Here!" },
{ 8, 8, 0, "Sorry..." },
{ 8, 9, 3, "I'm Ace in Team Rocket!"},
// 10 //
{ 11, 10, 3, "I know where she is."},
{ 11, 11, 0, "Rigth Side of Ice Cave..."} };
int Scenario[NUM_TOTAL_NPC][3] = 
{ {0,0,0}, {1,0,0}, {3,0,0}, {7,1,2}, {9,3,1}, {10, 4, 4} };

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
};

int NPCHandler::GetYesNext() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].YesNext; }
int NPCHandler::GetNoNext() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].NoNext; }
int NPCHandler::GetLink() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].link; }
int NPCHandler::GetSelect() { return Scenario[(Map.NPC[TalkNPC].story)][1]; }
int NPCHandler::GetLevel() { return Scenario[(Map.NPC[TalkNPC].story)][2]; }
const char *NPCHandler::GetData() { return talk_poke[Scenario[(Map.NPC[TalkNPC].story)][0]].data; }
void NPCHandler::SetYesNext() { Scenario[(Map.NPC[TalkNPC].story)][0] = GetYesNext(); }
void NPCHandler::SetNoNext() { Scenario[(Map.NPC[TalkNPC].story)][0] = GetNoNext(); }
