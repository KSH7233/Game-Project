#pragma once
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

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
#define FIRE 100
#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define BLACK SetConsoleTextAttribute( col,0x0000 )
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 )
#define GREEN SetConsoleTextAttribute( col,0x0002 )
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 )
#define BLOOD SetConsoleTextAttribute( col,0x0004 )
#define PUPPLE SetConsoleTextAttribute( col,0x0005 )
#define GOLD SetConsoleTextAttribute( col,0x0006 )		//색상 지정
#define WHITE SetConsoleTextAttribute( col,0x0007 )
#define GRAY SetConsoleTextAttribute( col,0x0008 )
#define BLUE SetConsoleTextAttribute( col,0x0009 )
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a )
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b )
#define RED SetConsoleTextAttribute( col,0x000c )
#define PLUM SetConsoleTextAttribute( col,0x000d )
#define YELLOW SetConsoleTextAttribute( col,0x000e )
class Fire
{
	int fireXpos;
	int fireYpos;
public:
	Fire(int x, int y) : fireXpos(x), fireYpos(y) {};
	void FireMove();
	void Go(int,int);
};
class MonsterBase
{
	int xPos, yPos, hp;
	bool isAlive;

public:
	MonsterBase(int x, int y, int hp) : xPos(x), yPos(y), hp(hp), isAlive(true) {};
	int GetXpos()const;
	int GetYPos()const;
	void SetXPos(int);
	void SetYPos(int);
	void Move();
};

class Monster : public MonsterBase
{
public:
	Monster() : MonsterBase(4, 17, 1) {};
};

class BossMonster : public MonsterBase
{
	bool fireReadyStatus;
	int bossShootTimer;
	Fire fire;
public:
	BossMonster() : MonsterBase(3, 18, 3), fireReadyStatus(true), bossShootTimer(0),fire(GetXpos(),GetYPos()) {};
	void Move();
	void ShootFire();
	Fire GetFire();
};

class GameManager
{
	Monster monster;
	BossMonster boss;
public:
	GameManager() {};
	void GameInit();
	void MoveMonster();
	void MapDraw();
};