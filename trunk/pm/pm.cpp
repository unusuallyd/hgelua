// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern HGE *hge;
HEFFECT effect;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	switch(hge->Input_GetKey())
	{
	case HGEK_ESCAPE: return true;
	case HGEK_UP:
		break;
	case HGEK_DOWN:
		break;
	}
	return false;
}
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);


	hge->Gfx_EndScene();
	return false;
}
int main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);

	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
		return 1;		
	}
	effect = hge->Effect_Load("sound/midi/14.mid");
	hge->System_Start();
	hge->System_Shutdown();
	hge->Release();

	return 0;
}

