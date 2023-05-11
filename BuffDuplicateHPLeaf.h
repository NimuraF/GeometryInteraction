#pragma once
#include "FriendlyLeaf.h"
class BuffDuplicateHPLeaf : public FriendlyLeaf {

public:
	BuffDuplicateHPLeaf(int, int, int, int HP = 1, COLORREF color = RGB(0, 255, 0));
	int Heal();

	virtual ~BuffDuplicateHPLeaf() {};
};

