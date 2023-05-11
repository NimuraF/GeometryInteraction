#pragma once
#include "Bird.h"
#include "IDanger.h"
class EnemyBird : public Bird, public IDanger {

public:
	EnemyBird(int, int, int, bool angle = false);
	int dealtDamage(int);
	virtual int calculateDamage(int);
};

