#include "Display.h"

Display::Display() {

}

Display::~Display() {

}

void Display::Init(int x, int y) {
	this->xpos = x;
	this->ypos = y;

	this->OnOrOff = new bool[8];
	memset(this->OnOrOff, 0, 8 * sizeof(bool));

	this->rects = new RECT[8];

	this->rects[0] = { x + 55, y + 22, x + 245, y + 44 };
	this->rects[1] = { x + 256, y + 55, x + 278, y + 278 };
	this->rects[2] = { x + 256, y + 322, x + 278, y + 545 };
	this->rects[3] = { x + 55, y + 556, x + 245, y + 578 };
	this->rects[4] = { x + 22, y + 322, x + 44, y + 545 };
	this->rects[5] = { x + 22, y + 55, x + 44, y + 278 };
	this->rects[6] = { x + 55, y + 289, x + 245, y + 311 };
	this->rects[7] = { x + 256, y + 556, x + 278, y + 578 };
}

void Display::Set(char HexValue) {
	for (int i = 7; i >= 0; i--) {
		int power = pow(2, i);
		if (HexValue >= power) {
			this->OnOrOff[i] = true;
			HexValue -= power;
		}
		else {
			this->OnOrOff[i] = false;
		}
	}
}

void Display::Draw(HDC hdc) {
	RECT rect = { this->xpos, this->ypos, this->xpos + 300, this->ypos + 600 };
	HBRUSH rectcol = CreateSolidBrush(RGB(180, 180, 180));
	FillRect(hdc, &rect, rectcol);

	HBRUSH segcoloff = CreateSolidBrush(RGB(100, 100, 100));
	HBRUSH segcolon = CreateSolidBrush(RGB(200, 100, 100));
	for (int i = 0; i < 8; i++) {
		if (this->OnOrOff[i] == true) {
			FillRect(hdc, &this->rects[i], segcolon);
		}
		else {
			FillRect(hdc, &this->rects[i], segcoloff);
		}
	}

	DeleteObject(rectcol);
	DeleteObject(segcoloff);
	DeleteObject(segcolon);
}

void Display::Destroy() {
	delete[] this->rects;
	delete[] this->OnOrOff;
}