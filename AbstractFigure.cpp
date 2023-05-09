#include "pch.h"
#include "AbstractFigure.h"

void AbstractFigure::setCoordinates(int X, int Y) {
	this->X = X;
	this->Y = Y;
}

void AbstractFigure::setSpeed(int speed) {
	this->speed = speed;
}

int AbstractFigure::getSpeed() {
	return this->speed;
}

int AbstractFigure::getX() {
	return this->X;
}

int AbstractFigure::getY() {
	return this->Y;
}

void AbstractFigure::setColor(COLORREF color) {
	this->color = color;
}

COLORREF AbstractFigure::getColor() {
	return this->color;
}