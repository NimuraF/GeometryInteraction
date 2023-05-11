#include "pch.h"
#include "RedBird.h"

RedBird::RedBird(int X, int Y, int speed, bool angle) : EnemyBird (X, Y, speed, angle) {
	this->setColor(RGB(255, 0, 0));
}

int RedBird::calculateDamage(int HP) {
	return HP / 4;
}