#include "header.h"

int main()
{
	GameManager manager;
	manager.GameInit();
	while (true)
	{
		manager.MoveMonster();
		manager.MapDraw();
		Sleep(100);
	}


}