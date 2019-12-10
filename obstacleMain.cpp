#include "obstacleHead.h"

int main()
{
	gameManager manager;
	boom boom(1, 17);
	stone stone(1,1);
	manager.mapping();
	manager.gameInit();
	while (true)
	{
		manager.mapDraw();
		boom.boomMove();
		stone.stoneAction();
		stone.stoneSwitch();
		Sleep(100);
	}


}