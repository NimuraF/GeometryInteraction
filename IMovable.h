#pragma once
class IMovable {

public:

	/* Обязываем наследников реализовать метод передвижения */
	virtual void move() = 0;
};

