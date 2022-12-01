
#include<iostream>
using namespace std;

#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <time.h>
#define WIDTH 40
#define HEIGHT 20 
#define BODY '*'
#define APPLE "0"

enum class Direction
{
	up,
	right,
	down,
	left
};

struct Point
{
	int x;
	int y;
};
//vector snake
vector<Point> snake = {
	Point{ WIDTH / 2 + 2, HEIGHT / 2 },
	Point{ WIDTH / 2 + 1, HEIGHT / 2 },
	Point{ WIDTH / 2, HEIGHT / 2 },
	Point{ WIDTH / 2 - 1, HEIGHT / 2 },
	Point{ WIDTH / 2 - 2, HEIGHT / 2 }
};
Direction direction = Direction::right;
Point apple;
Point prevTail;
int score = 0;
void drawSnakePart(Point);
void drawSnake();
void genApple();
void gotoxy(int, int);
void ShowConsoleCursor(bool);
void move();
void drawBox();
void drawHeadnTail();
bool isHitWall();
bool isAteApple();
void displayScore();
void showEndMenu();
void startGame();
void resetSnake();
void showStartMenu();




int main()
{
	showStartMenu();
	return 0;
}
void drawBox() // ve khung
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	gotoxy(0, HEIGHT);
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(WIDTH, i);
		cout << '|';
	}
}



bool isHitWall() //dam tuong
{
	return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}


void startGame() // bat dau game
{
	system("cls");
	ShowConsoleCursor(false);//An con tro chuot
	drawBox();
	drawSnake();//ve con ran
	genApple();

	while (true)//dinh nghia di chuyen ran
	{
		if (_kbhit())
		{
			char ch = _getch();
			ch = tolower(ch);
			if (ch == 'a' && direction != Direction::right)
				direction = Direction::left;
			else if (ch == 'w' && direction != Direction::down)
				direction = Direction::up;
			else if (ch == 's' && direction != Direction::up)
				direction = Direction::down;
			else if (ch == 'd' && direction != Direction::left)
				direction = Direction::right;

		}
		move();//di chuyen ran

		drawHeadnTail();//set lai ran moi
		Sleep(300);
		if (isAteApple())//An tao thi ran lon
		{
			score++;
			displayScore();
		}
		if (isHitWall())//dam tuong thi thoat
		{
			system("cls");
			return;
		}
	}

}

void showStartMenu()
{
		system("cls");
		ShowConsoleCursor(false);//An con tro chuot
		gotoxy(0, 3);
		Sleep(1000);
		for (size_t i = 3; i > 0; i--)
		{
			gotoxy(0, 3);
			cout << i << "         ";
			Sleep(1000);
		}
		gotoxy(0, 3);
		cout << "Bat dau!";
		Sleep(1000);

		startGame();
}
void drawSnakePart(Point p)//ve 1 diem tren than ran
{
	gotoxy(p.x, p.y);
	cout << BODY;
}

void drawSnake()//ve con ran
{
	for (size_t i = 0; i < snake.size(); i++)
		drawSnakePart(snake[i]);
}

void move()//di chuyen ran
{
	prevTail = snake.back();
	for (size_t i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	if (direction == Direction::up)
		snake[0].y -= 1;
	else if (direction == Direction::down)
		snake[0].y += 1;
	else if (direction == Direction::left)
		snake[0].x -= 1;
	else if (direction == Direction::right)
		snake[0].x += 1;
}

void drawHeadnTail()//tao vi tri moi, xoa vi tri cu khi di chuyen
{
	gotoxy(snake[0].x, snake[0].y);
	cout << BODY;
	gotoxy(prevTail.x, prevTail.y);
	cout << ' '; 
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
void ShowConsoleCursor(bool showFlag)// an con tro chuot
{
	HANDLE out =GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
//them tao
void genApple()
{
	srand(time(0));
	int x = rand() % (WIDTH - 1) + 1;
	int y = rand() % (HEIGHT - 1) + 1;
	apple = {
		x,
		y,
	};
	gotoxy(x, y);
	cout << "\033[1;31m" << APPLE << "\033[0m";
}
//An Tao
bool isAteApple()
{
	return snake[0].x == apple.x && snake[0].y == apple.y;
}
//Tinh diem 
void displayScore()
{
	gotoxy(WIDTH + 5, 2);
	cout << "DIEM: " << score;
}