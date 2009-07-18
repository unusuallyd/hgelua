#pragma once

#include <hge.h>
#include <hgesprite.h>

class HpBar
{
public:
	float m_w,m_h,m_border;
	float m_percent;
	float m_x, m_y;
	hgeQuad m_quadBorder, m_quadBack, m_quadFront;

	HpBar(float w, float h, float border);
	void Render();
	void SetColor();
	void SetPercent(float percent);
	void SetPos(float x, float y);
	void SetShape(float w, float h, float border);

};
