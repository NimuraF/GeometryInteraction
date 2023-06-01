#pragma once
#include "Point.h"
#include "IHitbox.h"
class Leaf : public Point, public IHitbox {

private:
	/* Точки хитбокса */
	int hitboxFX;
	int hitboxFY;
	int hitboxSX;
	int hitboxSY;

public:
	Leaf(int, int, int, COLORREF color = RGB(0, 0, 0));
	
	void Show();
	void move();

	void createHitbox();
	bool isIntersection(int, int, int, int);

	std::pair <std::pair <int, int>, std::pair <int, int> > getHB();
};

