#include "header.h"

int map[20][20] = { 0 };

void Fire::FireMove()
{
	map[fireYpos][fireXpos] = NULL;

	if (fireXpos >0)
	{
		this->fireXpos--;
	}
	else if (fireXpos ==0)
	{
		map[fireYpos][fireXpos] = NULL;
	}
	map[fireYpos][fireXpos] = FIRE;
}
void Fire::Go(int xPos, int yPos)
{
	fireXpos = xPos;
	fireYpos = yPos;
	map[this->fireXpos][this->fireXpos] = FIRE;
}

int MonsterBase::GetXpos()const { return xPos; }
int MonsterBase::GetYPos()const { return yPos; }
void MonsterBase::SetXPos(int x) { xPos = x; }
void MonsterBase::SetYPos(int y) { yPos = y; }
void MonsterBase::Move()
{
	int yPosition, xPosition;
	map[yPos][xPos] = NULL;
	srand((int)time(NULL));
	// 속도
	xPosition = rand() % (18 - 2 + 1) + 2; // 텔레포트 말고 움직임 1.왔다갔다 2. 한칸씩 더

	// 위치
	if (map[this->yPos][this->xPos] != WALL)
	{
		yPos = 18;
		xPos = xPosition;
	}
	map[yPos][xPos] = MONSTER;
}

Fire BossMonster::GetFire()
{
	return this->fire;
}
void BossMonster::ShootFire()
{
	fire.Go(this->GetXpos(),this->GetYPos());
}
void BossMonster::Move()
{
	int dTime = clock();
	int yPosition, xPosition;
	map[GetYPos()][GetXpos()] = NULL;
	srand((int)time(NULL));
	// 속도
	xPosition = rand() % (18 - 2 + 1) + 3; // 텔레포트 말고 움직임 1.왔다갔다 2. 한칸씩 더
	fire.FireMove();
	
	// 위치
	if (map[this->GetYPos()][this->GetXpos()] != WALL)
	{
		SetXPos(xPosition);
		SetYPos(17);
		if (dTime-this->bossShootTimer >= 3000)
		{
			fireReadyStatus = true;
			bossShootTimer = clock();
		}
		else
			fireReadyStatus = false;
		if (this->fireReadyStatus)
		{
			ShootFire();
		}
	}
	map[GetYPos()][GetXpos()] = BOSSMONSTER;
}



void GameManager::GameInit()
{
	CONSOLE_CURSOR_INFO info;
	HANDLE handle = col;
	info.bVisible = false;
	info.dwSize = 1;
	SetConsoleCursorInfo(handle, &info);
	char buf[256];
	sprintf_s(buf, "mode con: lines=%d cols=%d", HEIGHT + 1, (WIDTH * 2) + 1); //배열크기에 따라 조절
	system(buf);

}
void GameManager::MoveMonster()
{

	this->monster.Move();
	this->boss.Move();

}
void GameManager::MapDraw()
{

	boss.GetFire().FireMove();
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				YELLOW;
					cout << "▩";
				WHITE;
			}

			else if (map[y][x] == CHARACTER)
			{
				RED;
					cout << "옷";
				WHITE;
			}

			else if (map[y][x] == MONSTER)
			{
				BLUE;
					cout << "★";
				WHITE;
			}

			else if (map[y][x] == BOSSMONSTER)
			{
				BLUE;
					cout << "★";
				WHITE;
			}
			else if (map[y][x] == FIRE)
			{
				RED;
					cout << "$$";
				WHITE;
			}
			else if (map[y][x] == NULL)
				cout << "  ";
		}
		cout << endl;
	}
}