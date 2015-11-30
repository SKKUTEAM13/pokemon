#include <iostream>
#include <string>
using namespace std;

typedef struct
{
	int ID;
	string talk;
	int Yeslink;
	int Nolink;
	bool IsContinue;
}CONVERSATION;

CONVERSATION TALK[100];

void SetConver(void)
{
	{
		TALK[1].ID = 1;
		TALK[1].talk = "Jiwoo's group go through the Viridian Forest.";
		TALK[1].Yeslink = 2;
		TALK[1].Nolink = 0;
		TALK[1].IsContinue = true;
	}
	{
		TALK[2].ID = 2;
		TALK[2].talk = "Misty is Jiwoo's girlfriend.";
		TALK[2].Yeslink = 3;
		TALK[2].Nolink = 0;
		TALK[2].IsContinue = true;
	}
	{
		TALK[3].ID = 3;
		TALK[3].talk = "They are going to Viridian City to challenge the master.";
		TALK[3].Yeslink = 4;
		TALK[3].Nolink = 0;
		TALK[3].IsContinue = true;
	}
	{
		TALK[4].ID = 4;
		TALK[4].talk = "It's a nice day!";
		TALK[4].Yeslink = 5;
		TALK[4].Nolink = 0;
		TALK[4].IsContinue = true;
	}
	{
		TALK[5].ID = 5;
		TALK[5].talk = "It's a nice day!";
		TALK[5].Yeslink = 6;
		TALK[5].Nolink = 0;
		TALK[5].IsContinue = true;
	}
	{
		TALK[6].ID = 6;
		TALK[6].talk = "Pika-pika-";
		TALK[6].Yeslink = 0;
		TALK[6].Nolink = 0;
		TALK[6].IsContinue = false;
	}
	
}

int main(void)
{
	return 0;
}