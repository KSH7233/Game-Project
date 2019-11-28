#include <iostream>
#include <windows.h>
#include <conio.h>

#ifndef KEY_CODE
#define KEY_CODE

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

#endif

using namespace std;

void init();
void titleDraw();
void gotoxy(int x, int y);
int menuDraw();
int keyControl();
void infoDraw();
void drawMap();

char map[20][50] = {
	{"1111111111111111111111111111111111111111111111111"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"1000000000000000000000000000000000000000000000001"},
	{"10p0000000000000000000000000000000000000000000q01"},
	{"1111111111111111111111111111111111111111111111111"},
};

int main() {
	init();
	while (1) {
		titleDraw();
		int menuCode = menuDraw();
		if (menuCode == 0) {
			//게임시작
			drawMap();
		}
		else if (menuCode == 1) {
			//조작방법
			infoDraw();
		}
		else if (menuCode == 2) {
			//종료
			return 0;
		}
		system("cls");
	}
	return 0;
	
}
void init() {
	system("mode con cols=55 lines=25 | title 동영이의 슈퍼마리옹!");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);


}
void titleDraw() {
	cout << " " << endl << endl << endl;
	cout << "         ## ##      #     #####    ###     ### " << endl;
	cout << "        #  #  #    # #    #    #    #     #   #" << endl;
	cout << "        #  #  #    # #    #    #    #     #   #" << endl;
	cout << "        #     #   #####   #####     #     #   #" << endl;
	cout << "        #     #   #   #   #    #    #     #   #" << endl;
	cout << "        #     #   #   #   #    #    #     #   #" << endl;
	cout << "        #     #   #   #   #    #   ###     ### " << endl;

}
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
int menuDraw() {
	int x = 23;
	int y = 12;
	gotoxy(x-2,y);
	cout << "> 게임 시작";
	gotoxy(x, y+1);
	cout << "조작 방법";
	gotoxy(x, y+2);
	cout << "  종 료  ";
	while (1) {
		int n = keyControl();
		switch (n) {
			case UP: {
				if (y > 12) {
					gotoxy(x - 2, y);
					cout << " ";
					gotoxy(x - 2, --y);
					cout << ">";
		 		}
			 	break;
			}
			case DOWN: {
				if (y < 14) {
					gotoxy(x - 2, y);
					cout << " ";
					gotoxy(x - 2, ++y);
					cout << ">";
				}
				break;
			}
			case SUBMIT: {
				return y - 12;
			}
		}

		
	}
}
int keyControl() {
	char temp = getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SUBMIT;
	}

}
void infoDraw() {
	system("cls");
	cout << " " << endl << endl << endl;
	cout << "                [조작 방법] " << endl;
	cout << "              이동 : W S A D" << endl;
	cout << "              점프 : SPACEBAR" << endl;
	cout << "              제작자 : 정동영" << endl << endl;
	cout << "  메인 메뉴로 돌아갈려면 SPACE BAR를 누르시오" << endl;
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}

}
void drawMap() {
	system("cls");
	int h, w;

	for (h = 0; h < 20; h++) {
		for (w = 0; w < 50; w++) {
			char temp = map[h][w];
			if (temp == '0') {
				cout << " ";
			}
			else if (temp == '1') {
				cout << "#";
			}
			else if (temp == 'p') {
				cout << "@";
			}
			else if (temp == 'q') {
				cout << '0';
			}
		}
		cout << endl;
	}
	Sleep(3000);
}