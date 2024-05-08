#pragma once
#include <graphics.h>
#include <iostream>
#include <string>

#define WIDTH 1080
#define HEIGHT 720
#define R 1

using namespace std;

class Init
{
public:
	friend class Game;
	
	Init();

private:
	int Add[WIDTH];
	int Delete[WIDTH];

	int map[WIDTH/10][HEIGHT/10];

	int Num[WIDTH/10][HEIGHT/10];
};

class Game :public Init
{
public:
	void MouseOp();
	void Line();
	void PaintGame();
	void Eraser(int x, int y);
	void StatsNum(int x,int y,int flag);
	void UpdateGame();
	void Mod();
	void BeginE();

	int flag=0;
	int begin = 0;

};