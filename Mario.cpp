#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
//#define LEFT 75
//#define RIGHT 77
//#define UP 72
//#define DOWN 80
#define NULL 0
#define WALL 1
#define CHARACTER 2
#define FIRECHARACTER 3
#define FIREITEM 4
#define MONSTER 5
#define BOSS 6
#define OBSTACLE 7

#define WIDTH 20
#define HEIGHT 20




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
// 동적할당 어떻게 구현할 것인가 -> 맵을 입출력 하고 동적할당 해야할것 같다.

class Character //캐릭터 정보를 저장 및 현 캐릭터 이동 구현 코드
{
	int characterX;
	int characterY;
	bool fireShot;
	bool isJump;
public:
	Character() : characterX{ 1 }, characterY{ 10 }, fireShot{ 0 }, isJump{ 0 }{} //캐릭터 좌표 생성

	~Character() {}

	int getCharacterX() //x좌표 출력
	{
		return characterX;
	}

	int getCharacterY() //y좌표 출력
	{
		return characterY;
	}

	void characterMoveRight() //오른쪽 이동 입력
	{
		characterX++;
	}

	void characterMoveLeft() //왼쪽 이동 입력
	{
		characterX--;
	}

	void jumpCharacterY() //캐릭터 점프시 위로 한칸 이동
	{
		characterY--;
	}

	void fallCharacterY() //캐릭터 하강시 아래로 이동
	{
		characterY++;
	}

	int forUpperCheck() //캐릭터 위칸 체크
	{
		return --characterY;
	}

	int forBottomCheck() //캐릭터 아래칸 체크
	{
		return ++characterY;
	}

	int forLeftCheck() //캐릭터 왼칸 체크
	{
		return --characterX;
	}

	int forRightCheck() //캐릭터 오른칸 체크
	{
		return ++characterX;
	}

	bool normalState()
	{
		return fireShot;
	}




	/*void move() 캐릭터 이동 코드 direct class에서 구현
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			characterY--;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			characterY++;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			characterX--;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			characterX++;
		}
	}*/

};


class Director //감독 클래스 싱글톤 패턴을 이용하는 것 고려해야함 //다른것은 상태만 만들고 이건 움직임 및 표현을 구현한다.
{
	int map[HEIGHT][WIDTH] = { 0 }; //각각의 맵을 만들어야함 동적할당예정
	//파일입출력으로 맵에서 정보를 불러올시 각 클래스마다 집어 넣어 주어야함
public:

	//int getMap(int map[][WIDTH], int y, int x) //다른 클래스에서 맵의 오브젝트 찾기
	//{
	//	for (int i = 0; i < HEIGHT; i++)
	//	{
	//		for (int j = 0; j < WIDTH; j++)
	//		{
	//			if (i == y && j == x)
	//			{
	//				return map[i][j];
	//			}
	//		}
	//	}
	//}

	void gotoxy(int x, int y) //gotoxy이용 요함
	{
		COORD Pos;
		Pos.X = x;
		Pos.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	void CursorView(char show) //커서 깜빡임 제거
	{
		HANDLE hConsole;
		CONSOLE_CURSOR_INFO ConsoleCursor;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		ConsoleCursor.bVisible = show;
		ConsoleCursor.dwSize = 1;

		SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	}

	void Wall() //벽생성 //현상황 의미없음
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				map[0][j] = 1;
				map[HEIGHT - 1][j] = 1;
				map[i][0] = 1;
				map[i][WIDTH - 1] = 1;
			}
		}
	}

	void insertObject(Character& character) //각 객체들의 위치정보 맵에 넣기
	{
		map[character.getCharacterY()][character.getCharacterX()] = CHARACTER;//반환값 가져오기
	}

	void playerMove(Character& character) // 플레이어 기본움직임
	{		
		map[character.getCharacterY()][character.getCharacterX()] = NULL;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			character.jumpCharacterY();
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			character.fallCharacterY();
		}
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
		{
			character.characterMoveLeft();
		}
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
		{
			character.characterMoveRight();
		}
		map[character.getCharacterY()][character.getCharacterX()] = CHARACTER;	
		
	}

	void playerJump(Character& character) //공중시 움직임
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) //점프구현
		{
			for (int i = 0; i < 3; i++) //상승코드
			{
				system("cls");
				map[character.getCharacterY()][character.getCharacterX()] = NULL;
				/*if (map[character.forUpperCheck()][character.getCharacterX()] != WALL)*/ //벽충돌 오류
					character.jumpCharacterY();
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
					character.characterMoveLeft();
				else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
					character.characterMoveRight();
				map[character.getCharacterY()][character.getCharacterX()] = CHARACTER;
				mapDraw();
				Sleep(10);
			}

			for (int i = 0; i < 3; i++) //하강 코드
			{
				system("cls");
				map[character.getCharacterY()][character.getCharacterX()] = NULL;
				/*if (map[character.forBottomCheck()][character.getCharacterX()] != WALL) //벽충돌오류
				{
					
				}*/
				character.fallCharacterY();
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
					character.characterMoveLeft();
				else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
					character.characterMoveRight();
				map[character.getCharacterY()][character.getCharacterX()] = CHARACTER;
				if (i < 2)
					mapDraw();
				Sleep(10);
			}	

		}
		
	}

	void mapDraw() //화면에 출력하는 양식표현
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
						cout << "옷";
				}
				else if (map[y][x] == FIRECHARACTER)
				{
					RED
						cout << "옷";
					WHITE
				}
				else if (map[y][x] == FIREITEM)
				{
					YELLOW
						cout << "★";
					WHITE
				}
				else if (map[y][x] == MONSTER)
				{
					BLOOD
						cout << "＠";
					WHITE
				}
				else if (map[y][x] == BOSS)
				{
					BLOOD
						cout << "◎";
					WHITE
				}
				else if (map[y][x] == OBSTACLE)
				{
					BLOOD
						cout << "△";
					WHITE
				}
				else if (map[y][x] == NULL)
					cout << "  ";
			}
			cout << endl;
		}
	}
	
}; //class Director



class Object //아이템의 공통적 특성제작 추후 오버라이딩 //가상함수 사용
{
	int posX;
	int posY;

private:
	Object()//위치 초기화 //여기서 안해도 됨
	{
		
	}

	~Object()
	{

	}

	virtual void logic() = 0;

	//void gain() //획득시 코드 표현 가상함수로 자식에게 넘김 //direct에서 실행요함
	//{

	//}
};

class PowerItem : public Object //파이어 캐릭터로 만들기
{
public:
	void logic()
	{

	}
};

class FireBall : public Object //파이어 볼 위치
{
public:
	void logic()
	{

	}
};

class Obstacle : public Object//캐릭터와 겹쳤을때 확인 //장애물좌우아래가 캐릭터면 삭제
{
	void logic()
	{

	}
};

class Monster //캐릭터와 겹쳤을때 확인 //몬스터 좌우아래가 캐릭터면 캐릭터 삭제
{
	int spwanX;
	int spwanY;
	int hp;
public:
	void create()//가상함수
	{

	}
};



int main()
{
	Director dir;
	Character character;
	char show = 0;

	dir.insertObject(character);
	dir.Wall();
	dir.CursorView(show);
	while (1)
	{
		system("cls");
		if (kbhit())
		{
			dir.playerMove(character);
			dir.playerJump(character);
		}
		
		dir.mapDraw();
		
	}
}
