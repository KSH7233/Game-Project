#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define Y 0
#define X 1
#define CHARACTER 2
#define BOOM 5
#define STONE 10
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

class boom
{
	int boomYpos;
	int boomXpos;
public:
	boom(int x, int y) : boomXpos(x), boomYpos(y) {};
	void boomMove();

};

class stone
{
	int stoneXpos;
	int stoneYpos;
	bool switching = true;

public:
	stone(int x, int y) : stoneXpos(x), stoneYpos(y) {};
	void stoneAction();
	void stoneSwitch();
};

class gameManager
{
public:
	gameManager() {};
	void gameInit();
	void mapping();
	void mapDraw();
};
