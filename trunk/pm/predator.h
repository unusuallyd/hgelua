#pragma once

class _p
{
public:
	int x,y;
	int m_x1, m_x2, m_y1, m_y2;
	int m_speed;
	void randpos(int x1, int y1, int x2, int y2);
	void set_speed(int speed);
	int get_x();
	int get_y();
	void fixed_xy(int& x, int& y);
	virtual void move()=0;
};

class Predator;
class Prey;

class Predator: public _p
{
	Prey *m_ptr_Prey;
public:
	void set_target(Prey& p);
	virtual void move();
};

class Prey: public _p
{
	Predator *m_ptr_Predator;
public:
	void set_target(Predator& p);
	virtual void move();
};