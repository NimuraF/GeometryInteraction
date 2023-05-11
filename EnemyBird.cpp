#include "pch.h"
#include "EnemyBird.h"

EnemyBird::EnemyBird(int X, int Y, int speed, bool angle) : Bird(X, Y, speed, angle) {
	this->setColor(RGB(0, 0, 0));
}

int EnemyBird::dealtDamage(int HP) {
	HWND hwnd = ::FindWindow(NULL, L"Figures");
	SetTimer(hwnd, 8, 100, NULL);
	return this->calculateDamage(HP);
}

int EnemyBird::calculateDamage(int HP) {
	return 10;
}