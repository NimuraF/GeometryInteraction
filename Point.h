#pragma once
#include "AbstractFigure.h"
class Point : public AbstractFigure {

public:
	Point() = default;
	Point(int, int, int);

	void move();
	void Show();
	void Hide();

	virtual ~Point() {};
};

