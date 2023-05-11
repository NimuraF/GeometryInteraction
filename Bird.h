#pragma once
#include "Point.h"
#include "IHitbox.h"
class Bird : public Point, public IHitbox {
private:
	int hitboxFX;
	int hitboxFY;
	int hitboxSX;
	int hitboxSY;

	bool angle;

public:
	Bird(int, int, int, bool angle = false);

	void Show();

	void move();

	void setAngle(bool);
	bool getAngle();

	void createHitbox();
	bool isIntersection(int FX, int FY, int SX, int SY);

	std::pair <std::pair <int, int>, std::pair <int, int> > getHB();

	virtual ~Bird() {};
};

