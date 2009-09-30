#include "StdAfx.h"
#include "Predator.h"

//////////////////////////////////////////////////////////////////////////
// _p

void _p::randpos(float x1, float y1, float x2, float y2)
{
	m_x = (float)RandomInt((int)x1,(int)x2);
	m_y = (float)RandomInt((int)y1,(int)y2);
	m_x1 = x1 ; m_x2 = x2 ; m_y1 = y1 ; m_y2 = y2;
	m_tx = m_x1; m_ty = m_y1;
}

void _p::set_speed(float speed)
{
	 m_speed = speed;
}

float _p::get_x(){ return m_x;}
float _p::get_y(){ return m_y;}

void _p::fixed_xy()
{
	if (m_x < m_x1) m_x = m_x1;
	if (m_x > m_x2) m_x = m_x2;
	if (m_y < m_y1) m_y = m_y1;
	if (m_y > m_y2) m_y = m_y2;
}
void _p::move()
{
	if (on_edge())
	{
	}
}

void _p::moveto(float tx, float ty)
{
	m_tx = tx ; m_ty = ty;
	float dx = tx - m_x;
	float dy = ty - m_y;
	m_angle = atan(dy/dx);
}

bool _p::on_edge(float x, float y)
{
	if ( x - EP < m_x1 || x + EP > m_x2) return true;
	if ( y - EP < m_y1 || y + EP > m_y2) return true;
	return false;
}

bool _p::on_point(float x, float y)
{
	if ( abs(m_x - x) < EP || abs(m_y - y) < EP ) return true;
	else return false;
}
//////////////////////////////////////////////////////////////////////////
// Predator
void Predator::set_target(Prey &p)
{
	m_ptr_Prey = &p;
}

void Predator::move()
{

}
//////////////////////////////////////////////////////////////////////////
// Prey

void Prey::set_target(Predator& p)
{
	m_ptr_Predator = &p;
}

void Prey::move()
{

}