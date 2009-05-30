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
		hge->Effect_Play(effect);
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
	hge->System_SetState(HGE_LOGFILE, "game.log");

	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
		return 1;		
	}
	TexManager tex_manager;
	tex_manager.Init("script/tex.lua");
	SoundManager sound_manager;
	sound_manager.Init("script/sounds.lua");
	hge->System_Start();

	tex_manager.CleanUp();
	sound_manager.CleanUp();
	hge->System_Shutdown();
	hge->Release();

	return 0;
}

