#include<windows.h>
#include<iostream>
#include <cmath>
#include <conio.h>

#define SIZE 5
//#define WALL 10
//#define GRASS 10

using std::cout;
using std::cin;
using std::endl;
class MAP;


class RED
{
private:
	int location_row;
	int location_column;
public:
	RED();
	int Location_Red(void);
	void Move_Red(MAP& map, int move);
	friend class MAP;
};
class MAP
{
private:
	int location_row;
	int location_column;
	int map[SIZE][SIZE]; // 0 == '■' , 1 == '□' 2 == '▒'길인가 ( 1,2 =true 0 =false )
public:
	void Map_making(void);
	int Is_route(int location);
	void Map_printing(RED& red);//이 함수 안에 주인공의 위치를 받아서 주인공 위치 print
	friend class RED;
};

void MAP::Map_making(void)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			map[i][j] = 1;
		}
	}
	{
		map[0][0] = 0;
		map[1][0] = 0;
		map[2][0] = 0;
		map[3][0] = 0;
		map[1][2] = 0;
		map[1][3] = 0;
		map[4][2] = 0;
		map[4][3] = 0;
		map[4][4] = 0;

		map[2][2] = 2;
		map[2][3] = 2;
		map[3][2] = 2;
		map[3][3] = 2;
		map[3][1] = 2;
	}//map 모양 그리기
}
void MAP::Map_printing(RED& red)
{
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j= 0; j < SIZE; j++)
		{
			if(i*SIZE +j == red.Location_Red())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "■";
			}//hero가 있는 위치는 초록색 ■로 표시
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				
				if (Is_route(i*SIZE + j) == 0)
				{
					cout << "■";
				}
				else if (Is_route(i*SIZE + j) == 1)
				{
					cout << "□";
				}
				else if (Is_route(i*SIZE + j) == 2)
				{
					cout << "▒"; 
				}
			}
		}
		cout << endl;
	}
}
int MAP::Is_route(int location)
{
	return map[location / SIZE][location % SIZE];
}
RED::RED()
{
	location_row = SIZE-1;
	location_column = 0;
}
int RED::Location_Red(void)
{
	return location_row*SIZE + location_column;
}
void RED::Move_Red(MAP& map, int move)
{
	switch (move)
	{
	case 75:
		if (map.Is_route(location_row*SIZE + location_column-1) && location_column -1 >= 0)
		{
			location_column--;
		}
		break;
	case 77:
		if (map.Is_route(location_row * SIZE + location_column + 1) && location_column +1 < SIZE)
		{
			location_column++;
		}
		break;
	case 80:
		if (map.Is_route((location_row+1)*SIZE + location_column)&& location_row +1<SIZE)
		{
			location_row++;
		}
		break;
	case 72:
		if (map.Is_route((location_row-1)*SIZE + location_column)&& location_row-1 >= 0)
		{
			location_row--;
		}
		break;
	default:
		cout << "움직이는거 오류" << endl;
	}
}

int main()
{
	RED red;
	MAP beta;
	//printf("X:%d Y:%d\n", red.Location_Red() / SIZE, red.Location_Red() % SIZE);
	beta.Map_making();
	beta.Map_printing(red);
	
	int a;
	
	while(red.Location_Red() != SIZE-1)													//오른쪽 위쪽 모퉁이에 도착하면 끝
	{
		_getch();
		a = _getch();
		red.Move_Red(beta,a);
		beta.Map_printing(red);
		printf("%d\n", red.Location_Red());
		printf("X:%d Y:%d\n", red.Location_Red() / SIZE, red.Location_Red() % SIZE);
	}
	
	return 0;
}