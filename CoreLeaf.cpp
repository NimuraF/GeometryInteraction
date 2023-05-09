#include "pch.h"
#include "CoreLeaf.h"

extern HDC hdc;

CoreLeaf::CoreLeaf(int X, int Y, int speed, int HP, COLORREF color) : Leaf(X, Y, speed, color) {
	this->setHP(HP);
}

void CoreLeaf::Show() {
	int X = this->getX();
	int Y = this->getY();

	POINT myleaf[20] = {
	{ X, Y },
	{ X - 15, Y + 2 },
	{ X - 10, Y - 5 },
	{ X - 30, Y - 25 },
	{ X - 25, Y - 30 },
	{ X - 28, Y - 35 },
	{ X - 20, Y - 33 },
	{ X - 19, Y - 40 },
	{ X - 15, Y - 28 },
	{ X, Y - 50 },
	{ X + 15, Y - 28 },
	{ X + 19, Y - 40 },
	{ X + 20, Y - 33 },
	{ X + 28, Y - 35 },
	{ X + 25, Y - 30 },
	{ X + 30, Y - 25 },
	{ X + 10, Y - 5 },
	{ X + 15, Y + 2 },
	{ X, Y },
	{ X, Y + 20}
	};
	HBRUSH Brush = CreateSolidBrush(this->getColor());
	HPEN Pen = CreatePen(PS_SOLID, 2, this->getColor());
	SelectObject(hdc, Brush);
	SelectObject(hdc, Pen);
	wchar_t buffer[256];
	wsprintfW(buffer, L"%d", this->getHP());
	if (this->getHP() < 100) {
		TextOut(hdc, this->getX() - 7, this->getY() - 65, buffer, 2);
	}
	else {
		TextOut(hdc, this->getX() - 7, this->getY() - 65, buffer, 3);
	}
	Polygon(hdc, myleaf, 20);
	DeleteObject(Brush);
	DeleteObject(Pen);
}

void CoreLeaf::Hide() {

}

int CoreLeaf::getHP() {
	return this->HP;
}

void CoreLeaf::setHP(int HP) {
	if (this->getHP() < 125) {
		this->HP = HP;
	}
}