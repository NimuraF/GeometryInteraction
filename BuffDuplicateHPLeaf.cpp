#include "pch.h"
#include "BuffDuplicateHPLeaf.h"

extern int buffTimer;

BuffDuplicateHPLeaf::BuffDuplicateHPLeaf(int X, int Y, int speed, int HP, COLORREF color) : FriendlyLeaf(X, Y, speed, HP, color) {
	this->setHP(HP);
}

int BuffDuplicateHPLeaf::Heal() {
	HWND hwnd = ::FindWindow(NULL, L"Figures");
	SetTimer(hwnd, 9, 100, NULL);
	return 1;
}