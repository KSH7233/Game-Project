#include <iostream>
#include<conio.h>
#include<Windows.h>
#include <time.h>
using namespace std;
#define Y 0
#define X 1
#define CHARACTER 2
#define MONSTER 3
#define BOSSMONSTER 10
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20
#define WALL 1
#define NULL 0
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define WHITE SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////

int character[2];
int monster[2];
int bossMonster[2];
int map[HEIGHT][WIDTH] = { 0 };

void Move();
void monsterMove();
void MapDraw();
void Init();
void Initm();
void gotoxy(int x, int y);

int main()
{
	map[10][10] = CHARACTER;//INIT보다 먼저 설정되야함
	map[18][3] = MONSTER;
	map[17][3] = BOSSMONSTER;
	Init();
	Initm();
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[0][j] = WALL;
			map[HEIGHT - 1][j] = WALL;
			map[i][0] = WALL;
			map[i][WIDTH - 1] = WALL;
		}
	}
	while (1)
	{
		system("cls");
		MapDraw();
		if(kbhit())
		Move();
		monsterMove();
	}
}

void Init()
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 1;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width); //배열크기에 따라 조절
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
		}
	}
}

void Initm()
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 1;
	char buf[256];
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == MONSTER)
			{
				monster[X] = x;
				monster[Y] = y;
			}
			if (map[y][x] == BOSSMONSTER)
			{
				bossMonster[X] = x;
				bossMonster[Y] = y;
			}
		}
	}
}

void monsterMove() {
	int yPosition, xPosition;
	map[monster[Y]][monster[X]] = NULL;
	srand((int)time(NULL));
	xPosition = rand() % (18 - 2 +1) + 2;

	if (map[monster[Y]][monster[X]] != WALL)
	{
		monster[Y] = 18;
	}
	if (map[monster[Y]][monster[X]] != WALL)
	{
		monster[X] = xPosition;
	}
	map[monster[Y]][monster[X]] = MONSTER;

	map[bossMonster[Y]][bossMonster[X]] = NULL;
	if (map[bossMonster[Y]][bossMonster[X]] != WALL)
	{
				bossMonster[Y] = 17;
	}
	if (map[bossMonster[Y]][bossMonster[X]] != WALL) 
	{
				bossMonster[X] = xPosition;
	}
	map[bossMonster[Y]][bossMonster[X]] = BOSSMONSTER;
}

void Move()
{
	int ch;
	ch = getch();
	system("cls");
	
		if (ch == 224) {
			ch = getch();
			map[character[Y]][character[X]] = NULL;
			switch (ch)
			{
			case LEFT:
				if (map[character[Y]][character[X] - 1] != WALL)
				{
					character[X]--;
				}
				break;
			case RIGHT:
				if (map[character[Y]][character[X] + 1] != WALL)
				{
					character[X]++;
				}
				break;
			case UP:
				if (map[character[Y] - 1][character[X]] != WALL)
				{
					character[Y]--;
				}
				break;
			case DOWN:
				if (map[character[Y] + 1][character[X]] != WALL)
				{
					character[Y]++;
				}
				break;
			}
		}
		map[character[Y]][character[X]] = CHARACTER;
}

void MapDraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				YELLOW
					cout << "▩";
				WHITE
			}

			else if (map[y][x] == CHARACTER)
			{
				RED
					cout << "옷";
				WHITE
			}

			else if (map[y][x] == MONSTER)
			{
				BLUE
					cout << "★";
				WHITE
			}

			else if (map[y][x] == BOSSMONSTER)
			{
				BLUE
					cout << "★";
				WHITE
			}
			else if (map[y][x] == NULL)
				cout << "  ";
		}
		cout << endl;
	}
}

void gotoxy(int x, int y)
{
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}