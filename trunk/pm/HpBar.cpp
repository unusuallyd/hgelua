#include "StdAfx.h"
#include "HpBar.h"



HpBar::HpBar(float w, float h, float border)
{
	SetShape(w, h, border);
	SetPos(0,0);
	SetPercent(1);
	SetColor(HPBAR_COLOR_BORDER,HPBAR_COLOR_BACK,HPBAR_COLOR_FRONT);
}

void _SetAllColor(hgeQuad& quad, int color, float z)
{
	quad.tex = 0;
	for (int i=0; i<4; i++)
	{
		quad.v[i].col = color;
		quad.v[i].z = z;
	}
}
void HpBar::Render(HGE *hge)
{
	// quadBorder
	m_quadBorder.v[0].x = m_x, m_quadBorder.v[0].y = m_y;
	m_quadBorder.v[1].x = m_x + m_w, m_quadBorder.v[1].y = m_y;
	m_quadBorder.v[2].x = m_x + m_w, m_quadBorder.v[2].y = m_y + m_h;
	m_quadBorder.v[3].x = m_x, m_quadBorder.v[3].y = m_y + m_h;
	hge->Gfx_RenderQuad(&m_quadBorder);

	// quadBack
	m_quadBack.v[0].x = m_x + m_border, m_quadBack.v[0].y = m_y + m_border;
	m_quadBack.v[1].x = m_x + m_w - m_border, m_quadBack.v[1].y = m_y + m_border;
	m_quadBack.v[2].x = m_x + m_w - m_border, m_quadBack.v[2].y = m_y + m_h -m_border;
	m_quadBack.v[3].x = m_x +m_border, m_quadBack.v[3].y = m_y + m_h - m_border;
	hge->Gfx_RenderQuad(&m_quadBack);

	// quadFront
	m_quadFront.v[0].x = m_x + m_border, m_quadFront.v[0].y = m_y + m_border;
	m_quadFront.v[1].x = m_x + m_w * m_percent - m_border, m_quadFront.v[1].y = m_y + m_border;
	m_quadFront.v[2].x = m_x + m_w * m_percent - m_border, m_quadFront.v[2].y = m_y + m_h -m_border;
	m_quadFront.v[3].x = m_x +m_border, m_quadFront.v[3].y = m_y + m_h - m_border;
	hge->Gfx_RenderQuad(&m_quadFront);

}

void HpBar::SetPercent(float percent)
{
	m_percent = percent;
}

void HpBar::SetColor(int border, int back, int front)
{
	_SetAllColor(m_quadBorder,border, 0.6f);
	_SetAllColor(m_quadBack,back, 0.7f);
	_SetAllColor(m_quadFront,front, 0.8f);
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
