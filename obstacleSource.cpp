#include "obstacleHead.h"

int map[HEIGHT][WIDTH] = { NULL };

void boom::boomMove() // 폭탄의 움직임 랜덤성으로 구현.
{
	map[boomXpos][boomYpos] = NULL;
	int randomCount = rand() % 33;

	if (randomCount == 1 && map[boomXpos][boomYpos + 1] != WALL)
	{
		this->boomYpos++;
	}
	else if (randomCount == 2 && map[boomXpos][boomYpos - 1] != WALL)
	{
		this->boomYpos--;
	}
	map[boomXpos][boomYpos] = BOOM;

}

void stone::stoneSwitch() // 돌장애물의 상하 변경 함수.
{
	if (stoneXpos == 18)
	{
		switching = false;
	}

	else if (stoneXpos == 1)
	{
		switching = true;
	}
}

void stone::stoneAction()
{
	map[stoneXpos][stoneYpos] = NULL; // 상하운동하는 돌장애물

	if (stoneXpos>=1 && switching == true)
	{
		stoneXpos++;
	}

	else if (stoneXpos <= 18 && switching == false)
	{
		stoneXpos--;
	}
	map[stoneXpos][stoneYpos] = STONE;
}


void gameManager::gameInit()
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

void gameManager::mapping()
{
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
}

void gameManager::mapDraw()
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
			else if (map[y][x] == BOOM)
			{
				cout << "※";
			}
			else if (map[y][x] == STONE)
			{
				cout << "■";
			}

			else if (map[y][x] == NULL)
				cout << "  ";
		}
		cout << endl;
	}
}