#include "pch.h"
#include "Point.h"

extern HDC hdc;

Point::Point(int X, int Y, int speed) {
	this->setCoordinates(X, Y);
	this->setSpeed(speed);
}

void Point::move() {
	this->Hide();
	int speed = this->getSpeed();
	setCoordinates(getX() + speed, getY() + speed);
	this->Show();
}

void Point::Show() {
	SetPixel(hdc, getX(), getY(), this->getColor());
}

void Point::Hide() {
	COLORREF def = this->getColor();
	this->setColor(RGB(255, 255, 255));
	this->Show();
	this->setColor(def);
}