#pragma once

class _p
{
public:
	float m_x,m_y;
	float m_x1, m_x2, m_y1, m_y2;
	float m_tx, m_ty;
	float m_angle;
	float m_speed;
	void randpos(float x1, float y1, float x2, float y2);
	void set_speed(float speed);
	float get_x();
	float get_y();
	void fixed_xy();
	bool on_edge();
	bool on_point(float x, float y);
	virtual void move();
	virtual void moveto(float tx, float ty);
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