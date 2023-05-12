#pragma once
class AbstractFigure {

private:
	int X;
	int Y;
	int speed;
	COLORREF color;

public:
	virtual void move() = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;

	/* ������ �������������� �� ��������� */
	void setSpeed(int);
	int getSpeed();

	/* ������ �������������� � ������������*/
	void setCoordinates(int, int);
	int getX();
	int getY();

	/* ������ �������������� � ������ */
	void setColor(COLORREF color = RGB(0, 0, 0));
	COLORREF getColor();

	virtual ~AbstractFigure() {};
};

