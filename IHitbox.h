#pragma once
class IHitbox {

public:
	virtual void createHitbox() = 0;
	virtual bool isIntersection(int FX, int FY, int SX, int SY) = 0;
};

