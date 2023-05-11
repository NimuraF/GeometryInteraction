#include "pch.h"
#include "Bird.h"

extern HDC hdc;

Bird::Bird(int X, int Y, int speed, bool angle) : Point(X, Y, speed) {
	this->setSpeed(speed);
	this->setColor(RGB(255, 255, 255));
	this->angle = angle;
}

void Bird::Show() {
	int X = this->getX();
	int Y = this->getY();

	HPEN Pen = CreatePen(PS_SOLID, 5, this->getColor());
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X - 20, Y - 40);
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 20, Y - 40);
	DeleteObject(Pen);
}

void Bird::createHitbox() {
	this->hitboxFX = this->getX() - 20;
	this->hitboxFY = this->getY() - 40;
	this->hitboxSX = this->getX() + 20;
	this->hitboxSY = this->getY();
}

std::pair <std::pair <int, int>, std::pair <int, int> > Bird::getHB() {
	std::pair <std::pair <int, int>, std::pair <int, int>> Hitbox;
	Hitbox.first.first = this->hitboxFX;
	Hitbox.first.second = this->hitboxFY;
	Hitbox.second.first = this->hitboxSX;
	Hitbox.second.second = this->hitboxSY;
	return Hitbox;
}

bool Bird::isIntersection(int FX, int FY, int SX, int SY) {
	int x3 = max(FX, this->getHB().first.first);
	int y3 = max(FY, this->getHB().first.second);
	int x4 = min(SX, this->getHB().second.first);
	int y4 = min(SY, this->getHB().second.second);

	if ((x4 - x3) < 0 || (y4 - y3) < 0) {
		return false;
	}

	return true;
}

void Bird::move() {
	this->Hide();
	int speed = this->getSpeed();
	if (!angle) {
		setCoordinates(getX() + speed, getY() + speed);
	}
	else {
		setCoordinates(getX() + speed, getY() - speed);
	}
	this->Show();
}

bool Bird::getAngle() {
	return this->angle;
}

void Bird::setAngle(bool angle) {
	this->angle = angle;
}