#include "StdAfx.h"
#include "HpBar.h"


HpBar::HpBar(float w, float h, float border)
{
	SetShape(w, h, border);
	SetPos(0,0);
	SetPercent(100);
}

void HpBar::Render()
{

}

void HpBar::SetPercent(float percent)
{
	m_percent = percent;
}

void HpBar::SetColor()
{

}
void HpBar::SetPos(float x, float y)
{
	m_x = x;
	m_y = y;
}

void HpBar::SetShape(float w, float h, float border)
{
	m_w = w;
	m_h = h;
	m_border = border;
}
