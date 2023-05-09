#include "pch.h"
#include "FriendlyLeaf.h"


FriendlyLeaf::FriendlyLeaf(int X, int Y, int speed, int HP, COLORREF color) : Leaf(X, Y, speed, color) {
	this->setHP(HP);
}

int FriendlyLeaf::Heal() {
	return this->getHP();
}

int FriendlyLeaf::getHP() {
	return this->HP;
}

void FriendlyLeaf::setHP(int newHP) {
	this->HP = newHP;
}