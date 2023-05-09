#pragma once
#include "Leaf.h"
class CoreLeaf : public Leaf {

private:
	short buff;
	int HP;

public:
	CoreLeaf(int, int, int, int, COLORREF color = RGB(247, 85, 10));

	void Show();
	void Hide();

	void setHP(int);
	int getHP();
};

