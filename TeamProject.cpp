#include <iostream>
#include<conio.h>
#include<vector>
#include<Windows.h>
using namespace std;
#define HPUP 3
#define SPEEDUP 4
#define DAMAGEUP 5
#define USEDITEM 12
#define Y 0 // Y�� �� �ε���
#define X 1 // X�� �� �ε���
#define CHARACTER 2 // 
#define LEFT 75 // ���� ����Ű �ƽ�Ű�ڵ�
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20 // ���� ���α���
#define HEIGHT 20 // ���� ���α���
#define WALL 1 // ��
#define NULL 0 // ����
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//���� ����
#define WHITE SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////

class player
{
public:
	int hp = 100;
	int speed = 10;
	int damage = 3;
	void showStatus()
	{
		cout << "hp : " << hp << endl;
		cout << "speed : " << speed << endl;
		cout << "damage : " << damage << endl;
	}
};
class hpUp
{
public:
	int setHp(player& p, int map[HEIGHT][WIDTH])
	{ // ������ - ����ǥ�� �������� ������, ���� ���� ���� �ٽ� �� ��ġ�� �͵� ���� ������ �ʰ� �Ϸ���?
		if (map[2][2] == CHARACTER) // ĳ���Ͱ� �� ��ġ�� ������� �� ��ġ�� NULL���� ��
		{
			if (p.hp == 100)
			{
				p.hp += 10;
				map[2][2] = USEDITEM;
				return p.hp;
			}
		}
		else
		{
			return p.hp;
		}
	}
};
class speedUp
{
public:
	int setSp(player& p, int map[HEIGHT][WIDTH])
	{
		if (map[10][17] == CHARACTER)
			{
				if (p.speed == 3)
				{
					p.speed += 5;
					map[10][17] = USEDITEM;
					return p.speed;
				}
			}
		else
		{
			return p.speed;
		}
	}
};
class damageUp
{
public:
	int setDg(player& p, int map[HEIGHT][WIDTH])
	{
		if (map[15][15] == CHARACTER)
		{
			if (p.damage == 10)
			{
				p.damage += 2;
				map[15][15] = USEDITEM;
				return p.damage;
			}
		}
		else
		{
			return p.damage;
		}
	}
};

int character[2];
int hpup[2];
int speedup[2];
int damageup[3];
int map[HEIGHT][WIDTH] = { NULL }; // ���� ����
void Move();
void MapDraw();
void Init();
void gotoxy(int x, int y);

int main()
{
	vector<hpUp> item_h;
	vector<speedUp> item_s;
	vector<damageUp> item_d;  // vector �����̳� �ϳ��� �ٸ��Լ����� ���� Ŭ������ �� ������
	hpUp hp;
	speedUp sp;
	damageUp dg;

	item_h.push_back(hp);
	item_s.push_back(sp);
	item_d.push_back(dg);//Ŭ������ �´� ��ü�� �־������
//�����ڰ� �ִٸ� item.push_back(hp(10)); ���ڰ� �־������

	player ninja;

	map[10][10] = CHARACTER;//INIT���� ���� �����Ǿ���
	map[2][2] = HPUP;
	map[10][17] = SPEEDUP;
	map[15][15] = DAMAGEUP;
	Init();
	for (int i = 0; i < HEIGHT; i++)//���Է�
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[0][j] = WALL; // �� // map[y][x]
			map[HEIGHT - 1][j] = WALL; // �Ʒ�
			map[i][0] = WALL; // ����
			map[i][WIDTH - 1] = WALL;// ������
		}
	}
	while (1)
	{
		system("cls");
		MapDraw();
		if (map[2][2] == CHARACTER)
		{
			hp.setHp(ninja, map);
		}
		ninja.showStatus();
		if (kbhit())
		{
			Move(); // Ű����üũ �� ���ٲ�?
		}
	}
}

void Init() // ��ġ����
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width); //�迭ũ�⿡ ���� ����
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
			if (map[y][x] == HPUP)
			{
				hpup[X] = x;
				hpup[Y] = y;
			}
			if (map[y][x] == SPEEDUP)
			{
				speedup[X] = x;
				speedup[Y] = y;
			}
			if (map[y][x] == DAMAGEUP)
			{
				damageup[X] = x;
				damageup[Y] = y;
			}
		}
	}
}

void Move()
{
	int ch;
	ch = getch();

	{
		if (ch == 224)
		{
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
}

void MapDraw() // cout �뵵
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				YELLOW
					cout << "��";
				WHITE
			}
			else if (map[y][x] == HPUP)
			{
				GREEN
					cout << "HP";
				WHITE
			}
			else if (map[y][x] == SPEEDUP)
			{
				BLUE
					cout << "SP";
				WHITE
			}
			else if (map[y][x] == DAMAGEUP)
			{
				GOLD
					cout << "DG";
				WHITE
			}
			else if (map[y][x] == CHARACTER)
			{
				RED
					cout << "��";
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