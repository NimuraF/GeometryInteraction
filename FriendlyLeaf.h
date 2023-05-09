#pragma once
#include "Leaf.h"
#include "IUsable.h"

class FriendlyLeaf : public Leaf, public IUsable {

private:
	int HP;

public:
	FriendlyLeaf(int, int, int, int, COLORREF color = RGB(0, 255, 0));
	int Heal();

	void setHP(int);
	int getHP();
};

