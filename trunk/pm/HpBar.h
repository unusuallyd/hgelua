#pragma once

#include <hge.h>
#include <hgesprite.h>

#define HPBAR_COLOR_BORDER 0xff0000ff
#define HPBAR_COLOR_BACK 0xffffffff
#define HPBAR_COLOR_FRONT 0xff00ff00
class HpBar
{
public:
	float m_w,m_h,m_border;
	float m_percent;
	float m_x, m_y;
	hgeQuad m_quadBorder, m_quadBack, m_quadFront;

	HpBar(float w, float h, float border);
	void Render(HGE *hge);
	void SetColor(int border, int back, int front);
	void SetPercent(float percent);
	void SetPos(float x, float y);
	void SetShape(float w, float h, float border);

};
