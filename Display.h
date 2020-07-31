#pragma once
#include <cmath>
#include <stdio.h>
#include <Windows.h>

class Display {
private:
	int xpos, ypos;
	char value;

	RECT* rects;
	bool* OnOrOff;

public:
	Display();
	~Display();

	void Init(int x, int y);

	void Set(char HexValue);

	void Draw(HDC hdc);

	void Destroy();
};

