#include "StdAfx.h"
#include "Predator.h"

//////////////////////////////////////////////////////////////////////////
// _p

void _p::randpos(int x1, int y1, int x2, int y2)
{
	x = RandomInt(x1,x2);
	y = RandomInt(x1,x2);
	m_x1 = x1 ; m_x2 = x2 ; m_y1 = y1 ; m_y2 = y2;
}

void _p::set_speed(int speed)
{
	 m_speed = speed;
}

int _p::get_x(){ return x;}
int _p::get_y(){ return y;}

void _p::fixed_xy(int& x, int& y)
{
	if (x < m_x1) x = m_x1;
	if (x > m_x2) x = m_x2;
	if (y < m_y1) y = m_y1;
	if (y > m_y2) y = m_y2;
}
//////////////////////////////////////////////////////////////////////////
// Predator
void Predator::set_target(Prey &p)
{
	m_ptr_Prey = &p;
}

void Predator::move()
{
	if (m_ptr_Prey->x > x)
	{
		x+= m_speed;
	}else{
		x-= m_speed;
	}
	if (m_ptr_Prey->y > y)
	{
		y+= m_speed;
	}else{
		y-= m_speed;
	}
	fixed_xy(x, y);
}
//////////////////////////////////////////////////////////////////////////
// Prey

void Prey::set_target(Predator& p)
{
	m_ptr_Predator = &p;
}

void Prey::move()
{
	if (m_ptr_Predator->x > x)
	{
		x-= m_speed;
	}else{
		x+= m_speed;
	}
	if (m_ptr_Predator->y > y)
	{
		y-= m_speed;
	}else{
		y+= m_speed;
	}
	fixed_xy(x, y);
}