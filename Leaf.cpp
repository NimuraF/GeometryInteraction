#include "pch.h"
#include "Leaf.h"

extern HDC hdc;

Leaf::Leaf(int X, int Y, int speed, COLORREF color) : Point(X, Y, speed) {
	this->setColor(color);
	this->createHitbox();
}


void Leaf::Show() {
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
	Polygon(hdc, myleaf, 20);
	DeleteObject(Brush);
	DeleteObject(Pen);
}

void Leaf::move() {
	this->Hide();
	int speed = this->getSpeed();
	setCoordinates(getX(), getY() + speed);
	this->Show();
}

void Leaf::createHitbox() {
	this->hitboxFX = this->getX() - 31;
	this->hitboxFY = this->getY() - 50;
	this->hitboxSX = this->getX() + 31;
	this->hitboxSY = this->getY();
}


std::pair <std::pair <int, int>, std::pair <int, int> > Leaf::getHB() {
	std::pair <std::pair <int, int>, std::pair <int, int>> Hitbox;
	Hitbox.first.first = this->hitboxFX;
	Hitbox.first.second = this->hitboxFY;
	Hitbox.second.first = this->hitboxSX;
	Hitbox.second.second = this->hitboxSY;
	return Hitbox;
}

bool Leaf::isIntersection(int FX, int FY, int SX, int SY) {
	int x3 = max(FX, this->getHB().first.first);
	int y3 = max(FY, this->getHB().first.second);
	int x4 = min(SX, this->getHB().second.first);
	int y4 = min(SY, this->getHB().second.second);

	if ((x4 - x3) < 0 || (y4 - y3) < 0) {
		return false;
	}

	return true;
}