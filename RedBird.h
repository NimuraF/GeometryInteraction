#pragma once
#include "EnemyBird.h"

class RedBird : public EnemyBird {

public:
	RedBird(int, int, int, bool angle = false);

	int calculateDamage(int);
};

